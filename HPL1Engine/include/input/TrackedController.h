#ifndef HPL_TRACKED_CONTROLLER_H
#define HPL_TRACKED_CONTROLLER_H

#include "math/Math.h"
#include "vr/VRBackend.h"

namespace hpl {
  class TrackedController {
  public:
  	typedef cVRButtonState ButtonState;

    TrackedController();
    ~TrackedController();

  	void SetHand(eVRHand aHand);

    void SetMatrix(const cMatrixf& matrix);
    cMatrixf GetLastMatrix();
    cMatrixf GetMatrix();

    void SetVelocity(const cVector3f& velocity);
    cVector3f GetVelocity();

    void SetAngularVelocity(const cVector3f& angular_velocity);
    cVector3f GetAngularVelocity();


    void UpdateButtonState();
    ButtonState GetButtonState();

  private:
  	eVRHand hand_;
    ButtonState button_state_;
    cMatrixf last_matrix_;
    cMatrixf matrix_;
    cVector3f velocity_;
    cVector3f angular_velocity_;
  };
}
#endif