#include "ControllerManager.h"

int ControllerManager::refresh()
{
	DWORD res;
	XINPUT_STATE state;

	ZeroMemory(&state, sizeof(XINPUT_STATE));

	res = XInputGetState(0, &state);

	if (res == ERROR_SUCCESS)
	{
		user = state.Gamepad;
	}

	return 0;
}

bool ControllerManager::isControllerConnected()
{
	DWORD res;
	XINPUT_STATE state;

	ZeroMemory(&state, sizeof(XINPUT_STATE));

	res = XInputGetState(0, &state);

	if (res == ERROR_SUCCESS)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool ControllerManager::isAButtonPressed()
{
	return ((user.wButtons & XINPUT_GAMEPAD_A) != 0);
}

bool ControllerManager::isBButtonPressed()
{
	return ((user.wButtons & XINPUT_GAMEPAD_B) != 0);
}

bool ControllerManager::isXButtonPressed()
{
	return ((user.wButtons & XINPUT_GAMEPAD_X) != 0);
}

bool ControllerManager::isYButtonPressed()
{
	return ((user.wButtons & XINPUT_GAMEPAD_Y) != 0);
}

bool ControllerManager::isDPadDownPressed()
{
	return ((user.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) != 0);
}

bool ControllerManager::isDPadUpPressed()
{
	return ((user.wButtons & XINPUT_GAMEPAD_DPAD_UP) != 0);
}

bool ControllerManager::isDPadLeftPressed()
{
	return ((user.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) != 0);
}

bool ControllerManager::isDPadRightPressed()
{
	return ((user.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) != 0);
}

bool ControllerManager::isLBButtonPressed()
{
	return ((user.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) != 0);
}

bool ControllerManager::isRBButtonPressed()
{
	return ((user.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) != 0);
}

bool ControllerManager::isBackButtonPressed()
{
	return ((user.wButtons & XINPUT_GAMEPAD_BACK) != 0);
}

bool ControllerManager::isStartButtonPressed()
{
	return ((user.wButtons & XINPUT_GAMEPAD_START) != 0);
}

bool ControllerManager::isLeftJoystickPressed()
{
	return ((user.wButtons & XINPUT_GAMEPAD_LEFT_THUMB) != 0);
}

bool ControllerManager::isRightJoystickPressed()
{
	return ((user.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) != 0);
}

float ControllerManager::checkLeftTrigger()
{
	return (float)(user.bLeftTrigger / 255);
}

float ControllerManager::checkRightTrigger()
{
	return (float)(user.bRightTrigger / 255);
}

fvector2D ControllerManager::checkLeftStick()
{
	float deadZoneX = 0.05f;
	float deadZoneY = 0.05f;

	float normalLX = fmaxf(-1, (float)user.sThumbLX / 32767);
	float normalLY = fmaxf(-1, (float)user.sThumbLY / 32767);

	float finalX = ((fabs(normalLX) < deadZoneX) ? 0 : (fabs(normalLX) - deadZoneX) * (normalLX / fabs(normalLX)));
	float finalY = ((fabs(normalLY) < deadZoneY) ? 0 : (fabs(normalLY) - deadZoneY) * (normalLY / fabs(normalLY)));

	if (deadZoneX > 0)
	{
		finalX /= 1 - deadZoneX;
	}

	if (deadZoneY > 0)
	{
		finalY /= 1 - deadZoneY;
	}

	return fvector2D(finalX, finalY);
}

fvector2D ControllerManager::checkRightStick()
{
	float deadZoneX = 0.05f;
	float deadZoneY = 0.05f;

	float normalRX = fmaxf(-1, (float)user.sThumbRX / 32767);
	float normalRY = fmaxf(-1, (float)user.sThumbRY / 32767);

	float finalX = ((fabs(normalRX) < deadZoneX) ? 0 : (fabs(normalRX) - deadZoneX) * (normalRX / fabs(normalRX)));
	float finalY = ((fabs(normalRY) < deadZoneY) ? 0 : (fabs(normalRY) - deadZoneY) * (normalRY / fabs(normalRY)));

	if (deadZoneX > 0)
	{
		finalX /= 1 - deadZoneX;
	}

	if (deadZoneY > 0)
	{
		finalY /= 1 - deadZoneY;
	}

	return fvector2D(finalX, finalY);
}