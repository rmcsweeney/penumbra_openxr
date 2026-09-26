//
// Created by ryan on 9/25/26.
//

#include "vr/VRBackendOpenVR.h"

#include "system/LowLevelSystem.h"
#include "OpenVRMath.h"

namespace hpl
{

	namespace
	{

		void LogCompositorError(vr::EVRCompositorError aError)
		{
			if (aError != vr::VRCompositorError_None)
			{
				Warning("OpenVR Compositor Error: %d\n", int(aError));
			}


		}

		cVector3f ToVector(const vr::HmdVector3_t &v)
		{
			return cVector3f(v.v[0], v.v[1], v.v[2]);
		}

		vr::EVREye ToOpenVREye(eVREye aEye)
		{
			return aEye == eVREye_Left ? vr::Eye_Left : vr::Eye_Right;
		}
	}

	cVRBackendOpenVR::cVRBackendOpenVR()
		: mpHMD(nullptr), mlEyeWidth(0), mlEyeHeight(0)
	{

	}

	cVRBackendOpenVR::~cVRBackendOpenVR()
	{
		Shutdown();
	}

	bool cVRBackendOpenVR::Init()
	{
		vr::EVRInitError error = vr::VRInitError_None;
		vr::IVRSystem *pHMD = vr::VR_Init(&error, vr::VRApplication_Scene);
		if (error != vr::VRInitError_None)
		{
			Warning("VR Init Error: %s\n", vr::VR_GetVRInitErrorAsEnglishDescription(error));
			return false;
		}
		if (vr::VRCompositor() == nullptr)
		{
			Warning("OpenVR compositor unavailable\n");
			return false;
		}

		uint32_t w, h;
		pHMD->GetRecommendedRenderTargetSize(&w, &h);
		mlEyeWidth = static_cast<int>(w);
		mlEyeHeight = static_cast<int>(h);

		mpHMD = pHMD;
		Log("OpenVR initialized with eye size %dx%d\n", mlEyeWidth, mlEyeHeight);
		return true;
	}

	void cVRBackendOpenVR::Shutdown()
	{
		if (mpHMD)
		{
			vr::VR_Shutdown();
			mpHMD = nullptr;
		}
	}

	//updates locations of head and hand trackers in the data, then reads button inputs
	void cVRBackendOpenVR::BeginFrame()
	{
		if (!mpHMD)
		{
			return;
		}

		vr::TrackedDevicePose_t poses[vr::k_unMaxTrackedDeviceCount];
		vr::VRCompositor()->WaitGetPoses(poses,
			vr::k_unMaxTrackedDeviceCount,
			nullptr,
			0);

		const vr::TrackedDevicePose_t &hmd = poses[vr::k_unTrackedDeviceIndex_Hmd];
		mHead.valid = hmd.bPoseIsValid;
		if (hmd.bPoseIsValid)
		{
			mHead.mtx = FromOpenVR(hmd.mDeviceToAbsoluteTracking); //updating head location
		}

		const vr::ETrackedControllerRole roles[2] = {
			vr::TrackedControllerRole_LeftHand, //eVRHand_Left
			vr::TrackedControllerRole_RightHand //eVRHand_Right
		};

		for (int i = 0; i < 2; ++i)
		{
			mHands[i].valid = false;
			mButtons[i].valid = false; //buttons already contains current L/R

			vr::TrackedDeviceIndex_t d = mpHMD->GetTrackedDeviceIndexForControllerRole(roles[i]);
			if (d == vr::k_unTrackedDeviceIndexInvalid || !poses[d].bPoseIsValid)
			{
				continue; //don't update an untracked hand--ie hand behind body on inside-out tracking
			}

			const vr::TrackedDevicePose_t &p = poses[d];
			mHands[i].mtx = FromOpenVR(p.mDeviceToAbsoluteTracking);
			mHands[i].velocity = ToVector(p.vVelocity);
			mHands[i].angularVelocity = ToVector(p.vAngularVelocity);
			mHands[i].valid = true;

			ReadButtons(d, mButtons[i]);
		}

		vr::VREvent_t ev;
		while (mpHMD->PollNextEvent(&ev, sizeof(ev)))
		{
			switch (ev.eventType)
			{
			case vr::VREvent_TrackedDeviceActivated:	Log("VR device %u attached\n", ev.trackedDeviceIndex); break;
			case vr::VREvent_TrackedDeviceDeactivated:	Log("VR device %u detached\n", ev.trackedDeviceIndex); break;
			case vr::VREvent_TrackedDeviceUpdated:		Log("VR device %u updated\n", ev.trackedDeviceIndex); break;
			default: break;
			}
		}
	};

	void cVRBackendOpenVR::ReadButtons(unsigned int alDevice, cVRButtonState& aOut)
	{
		vr::VRControllerState_t s;
		if (!mpHMD->GetControllerState(alDevice, &s))
		{
			return;
		}

		auto pressed = [&](vr::EVRButtonId b)
		{ return (s.ulButtonPressed & vr::ButtonMaskFromId(b)) != 0; };
		auto touched = [&](vr::EVRButtonId b)
		{ return (s.ulButtonTouched & vr::ButtonMaskFromId(b)) != 0; };

		aOut.touchContact	= touched(vr::k_EButton_SteamVR_Touchpad);
		aOut.padPressed		= pressed(vr::k_EButton_SteamVR_Touchpad);
		aOut.gripPressed	= pressed(vr::k_EButton_Grip);
		aOut.triggerPressed	= pressed(vr::k_EButton_SteamVR_Trigger);
		aOut.touchX = s.rAxis[0].x;
		aOut.touchY = s.rAxis[0].y;
		aOut.triggerMargin = s.rAxis[1].x;

		aOut.valid = true;
	}

	cVREyeView cVRBackendOpenVR::GetEyeView(eVREye aEye) const
	{
		cVREyeView view;
		if (!mpHMD)
		{
			return view;
		}
		//get which eye we are looking through, left or right, then apply the transform from our head's position
		vr::EVREye eye = ToOpenVREye(aEye);
		mpHMD->GetProjectionRaw(eye, &view.tanLeft, &view.tanRight, &view.tanUp, &view.tanDown);
		view.eyeToHead = FromOpenVR(mpHMD->GetEyeToHeadTransform(eye));
		return view;
	}

	void cVRBackendOpenVR::SubmitEye(eVREye aEye, unsigned int alGLTexture)
	{
		if (!mpHMD)
		{
			return;
		}

		vr::Texture_t tex = {
			(void*)(uintptr_t) alGLTexture,
			vr::API_OpenGL,
			vr::ColorSpace_Gamma
		};
		LogCompositorError(vr::VRCompositor()->Submit(ToOpenVREye(aEye), &tex));
	}
}
