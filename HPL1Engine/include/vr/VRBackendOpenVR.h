//
// Created by ryan on 9/25/26.
//

#ifndef PENUMBRAOPENXR_VRBACKENDOPENVR_H
#define PENUMBRAOPENXR_VRBACKENDOPENVR_H

#include "vr/VRBackend.h"

namespace vr { class IVRSystem; }

namespace hpl
{
	class cVRBackendOpenVR: public iVRBackend
	{
	public:
		cVRBackendOpenVR();
		~cVRBackendOpenVR() override;

		//Lifetime
		bool Init() override;
		void Shutdown() override;
		bool IsActive() const override { return mpHMD != nullptr; };

		//per frame
		void BeginFrame() override;
		void EndFrame() override;

		//tracking
		cVRPose GetHeadPose() const override { return mHead; };
		cVRPose GetHandPose(eVRHand aHand) const override { return mHands[aHand]; };
		cVRButtonState GetButtons(eVRHand aHand) const override { return mButtons[aHand]; };

		//rendering
		void GetEyeSize(int& alWidth, int& alHeight) const override { mlEyeWidth = alWidth; mlEyeHeight = alHeight; };
		cVREyeView GetEyeView(eVREye aEye) const override;
		void SubmitEye(eVREye aEye, unsigned int alGLTexture) override;

		bool GetPlayAreaSize(float &afWidth, float &afDepth) const override;

	private:
		void ReadButtons(unsigned int alDevice, cVRButtonState &aOut);

		vr::IVRSystem *mpHMD;
		mutable int mlEyeWidth;
		mutable int mlEyeHeight;

		cVRPose mHead;
		cVRPose mHands[2];
		cVRButtonState mButtons[2];

	};
}
#endif //PENUMBRAOPENXR_VRBACKENDOPENVR_H
