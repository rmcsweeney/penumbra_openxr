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
		bool Init() override { return true; }
		void Shutdown() override {}
		bool IsActive() const override { return false; }

		void BeginFrame() override {};
		void EndFrame() override {};

		cVRPose GetHeadPose() const override { return cVRPose(); };
		cVRPose GetHandPose(eVRHand aHand) const override { return cVRPose(); };
		cVRButtonState GetButtons(eVRHand aHand) const override { return cVRButtonState(); };

		void GetEyeSize(int& w, int& h) const override { w = 0; h = 0; };
		cVREyeView GetEyeView(eVREye aEye) const override { return cVREyeView(); };
		void SubmitEye(eVREye aEye, unsigned int alGLTexture) override {};
	};
}


#endif //PENUMBRAOPENXR_VRBACKENDOPENVR_H
