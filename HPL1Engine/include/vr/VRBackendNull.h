//
// Created by ryan on 9/25/26.
//

#ifndef PENUMBRAOPENXR_VRBACKENDNULL_H
#define PENUMBRAOPENXR_VRBACKENDNULL_H

#include "vr/VRBackend.h"

namespace hpl
{

	class cVRBackendNull : public iVRBackend
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

		bool GetPlayAreaSize(float &w, float &d) const override { w = 0; d = 0; return false; }
	};
}

#endif //PENUMBRAOPENXR_VRBACKENDNULL_H
