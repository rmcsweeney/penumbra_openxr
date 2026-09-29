#include "input/TrackedController.h"

#include "game/Game.h"

using namespace hpl;

namespace hpl {
  extern cGame* gGame;
}

TrackedController::TrackedController() : hand_(eVRHand_Right)
{
}

TrackedController::~TrackedController() {
}

void TrackedController::SetHand(eVRHand aHand)
{
	hand_ = aHand;
}

void TrackedController::SetMatrix(const cMatrixf& matrix) {
  last_matrix_ = matrix_;
  matrix_ = matrix;
}

cMatrixf TrackedController::GetLastMatrix() {
  return last_matrix_;
}

cMatrixf TrackedController::GetMatrix() {
  return matrix_;
}

void TrackedController::SetVelocity(const cVector3f& velocity) {
  velocity_ = velocity;
}

cVector3f TrackedController::GetVelocity() {
  return velocity_;
}
void TrackedController::SetAngularVelocity(const cVector3f& angular_velocity) {
  angular_velocity_ = angular_velocity;
}

cVector3f TrackedController::GetAngularVelocity() {
  return angular_velocity_;
}

void TrackedController::UpdateButtonState() {
	cVRButtonState raw;
	if (gGame && gGame->mpVR)
	{
		raw = gGame->mpVR->GetButtons(hand_);
	}

	ButtonState &s = button_state_;

	s.gripJustPressed		= raw.gripPressed		&& !s.gripJustPressed;
	s.gripJustReleased		= !raw.gripPressed		&& s.gripPressed;
	s.padJustPressed		= raw.padPressed		&& !s.padPressed;
	s.padJustReleased		= !raw.padPressed		&& s.padPressed;
	s.touchJustContacted	= raw.touchContact		&& !s.touchContact;
	s.touchJustReleased		= !raw.touchContact		&& s.touchContact;
	s.triggerJustPressed	= raw.triggerPressed	&& !s.triggerPressed;
	s.triggerJustReleased	= !raw.triggerPressed	&& s.triggerPressed;
	s.menuJustPressed		= raw.menuPressed		&& !s.menuPressed;
	s.menuJustReleased		= !raw.menuPressed		&& s.menuPressed;

	s.gripPressed = raw.gripPressed;
	s.padPressed = raw.padPressed;
	s.touchContact = raw.touchContact;
	s.triggerPressed = raw.triggerPressed;
	s.menuPressed = raw.menuPressed;

	s.touchX = raw.touchX;
	s.touchY = raw.touchY;
	s.triggerMargin = raw.triggerMargin;
	s.valid = raw.valid;

}

TrackedController::ButtonState TrackedController::GetButtonState() {
  return button_state_;
}