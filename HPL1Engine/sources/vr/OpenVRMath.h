#ifndef HPL_OPENVR_MATH_H
#define HPL_OPENVR_MATH_H

#include <openvr.h>
#include <math/MathTypes.h>

namespace hpl
{
	inline cMatrixf FromOpenVR(const vr::HmdMatrix34_t& a)
	{
		hpl::cMatrixf mat;

		for (int r = 0; r < 3; r++)
		{
			for (int c = 0; c < 4; c++)
			{
				mat.m[r][c] = a.m[r][c];
			}

		}
		mat.m[3][0] = 0;
		mat.m[3][1] = 0;
		mat.m[3][2] = 0;
		mat.m[3][3] = 1;

		return mat;
	}

	inline cMatrixf FromOpenVR(const vr::HmdMatrix44_t& a)
	{
		hpl::cMatrixf mat;

		for (int r = 0; r < 4; r++)
		{
			for (int c = 0; c < 4; c++)
			{
				mat.m[r][c] = a.m[r][c];
			}

		}

		return mat;
	}
}
#endif