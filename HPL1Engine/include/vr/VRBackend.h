//
// Created by ryan on 9/25/26.
//

#ifndef PENUMBRAOPENXR_VRBACKEND_H
#define PENUMBRAOPENXR_VRBACKEND_H
#include "vr/VRTypes.h"

namespace hpl
{
	enum eVREye		{ eVREye_Left, eVREye_Right };
	enum eVRHand	{ eVRHand_Left, eVRHand_Right };

	class iFrameBuffer;

	class iVRBackend
	{
		public:
		virtual ~iVRBackend() = default;

		virtual bool Init() = 0;
		virtual void Shutdown() = 0;
		virtual bool IsActive() const = 0;

		virtual void BeginFrame() = 0;
		virtual void EndFrame() = 0;

		virtual cVRPose GetHeadPose() const = 0;
		virtual cVRPose GetHandPose(eVRHand aHand) const = 0;
		virtual cVRButtonState GetButtons(eVRHand aHand) const = 0;

		virtual void GetEyeSize(int &alWidth, int &alHeight) const = 0;
		virtual cVREyeView GetEyeView(eVREye aEye) const = 0;
		virtual void SubmitEye(eVREye aEye, unsigned int alGLTexture) = 0;
	};


}

#endif //PENUMBRAOPENXR_VRBACKEND_H
