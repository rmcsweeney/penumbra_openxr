//
// Created by ryan on 9/25/26.
//

#ifndef PENUMBRAOPENXR_VRTYPES_H
#define PENUMBRAOPENXR_VRTYPES_H
#include "math/MathTypes.h"

namespace hpl
{
	struct cVRPose
	{
		cMatrixf mtx = cMatrixf::Identity;
		cVector3f velocity = cVector3f(0,0,0);
		cVector3f angularVelocity = cVector3f(0,0,0);
		bool valid = false;
	};

	struct cVREyeView
	{
		cMatrixf eyeToHead = cMatrixf::Identity;
		//measured in radians in OpenXR
		float fovLeft = 0, fovRight = 0, fovUp = 0, fovDown = 0;
	};

	//TODO: currently maps Vive-style controller
	struct cVRButtonState
	{
		float touchX = 0.0, touchY = 0.0;
		bool touchContact = false, touchJustContacted = false, touchJustReleased = false;
		bool padPressed = false, padJustPressed = false, padJustReleased = false;
		bool gripPressed = false, gripJustPressed = false, gripJustReleased = false;
		float triggerMargin = 0.0;
		bool triggerPressed = false, triggerJustPressed = false, triggerJustReleased = false;
		bool menuPressed = false, menuJustPressed = false, menuJustReleased = false;
		bool valid = false;
	};
}


#endif //PENUMBRAOPENXR_VRTYPES_H
