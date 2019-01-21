#ifndef CONTROLLERMANAGER_H
#define CONTROLLERMANAGER_H
#include <Windows.h>
#include <Xinput.h>
//#include <math.h>
#include "structs.h"

class ControllerManager
{
	private:
		XINPUT_GAMEPAD user;

	public:
		ControllerManager() {}
		int refresh();

		bool isControllerConnected();

		//checking actual button and trigger presses
		//if more than one controller should pass a port No.
		bool isAButtonPressed();
		bool isBButtonPressed();
		bool isXButtonPressed();
		bool isYButtonPressed();

		bool isStartButtonPressed();
		bool isBackButtonPressed();

		bool isRBButtonPressed();
		bool isLBButtonPressed();

		bool isDPadUpPressed();
		bool isDPadDownPressed();
		bool isDPadRightPressed();
		bool isDPadLeftPressed();

		bool isLeftJoystickPressed();
		bool isRightJoystickPressed();
		fvector2D checkLeftStick();
		fvector2D checkRightStick();

		float checkRightTrigger();
		float checkLeftTrigger();
};
#endif
