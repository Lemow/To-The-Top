#include "Input.h"
#include <iostream>
#include <GLFW/glfw3.h>
KeyState Input::keys[(int)Key::MAX_KEY] = {};
Gamepad Input::gamepads[4] = {};
uint32_t Input::activeGamepads = 0;
float Input::MouseX = 0.0f, Input::MouseY = 0.0f;

KeyState Input::GetKey(Key key)
{
	return keys[(int)key];
}

void Input::SetKey(Key key, KeyState state)
{
	keys[(int)key] = state;
}

void Input::ScanKeys()
{
	static KeyState lastButtons[4][14] = {};
	int presents[4];
	activeGamepads = 0;
	presents[0] = glfwJoystickPresent(GLFW_JOYSTICK_1);
	presents[1] = glfwJoystickPresent(GLFW_JOYSTICK_2);
	presents[2] = glfwJoystickPresent(GLFW_JOYSTICK_3);
	presents[3] = glfwJoystickPresent(GLFW_JOYSTICK_4);

	for (int gamepad = 0; gamepad < 4; gamepad++)
	{
		if (presents[gamepad] == 1)
		{
			activeGamepads++;
			int axesCount;
			const float* axes = glfwGetJoystickAxes(gamepad, &axesCount);
			for (int i = 0; i < axesCount; i++)
			{
				float axis = axes[i];
				if (i == (int)GamepadAxis::RT || i == (int)GamepadAxis::LT)
				{
					axis = (axis + 1.0f)/ 2.0f;
					gamepads[gamepad].axes[i] = axis;
					continue;
				}

				if (std::abs(axis) < 0.2f)
				{
					Input::gamepads[gamepad].axes[i] = 0.0f;
				}
				else
				{
					if (axes[i] > 0.0f)
					{
						gamepads[gamepad].axes[i] = axis - 0.2f;
					}
					else
						gamepads[gamepad].axes[i] = axis + 0.2f;
				}
			}
			int buttonCount;
			const unsigned char* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCount);
			for (int i = 0; i < buttonCount; i++)
				if (buttons[i] == GLFW_PRESS)
					gamepads[gamepad].buttons[i] = KeyState::KeyPress;
				else if (buttons[i] == GLFW_RELEASE)
					gamepads[gamepad].buttons[i] = KeyState::KeyRelease;
			for (int i = 0; i < buttonCount; i++)
			{
				if (gamepads[gamepad].buttons[i] == KeyState::KeyRelease && (lastButtons[gamepad][i] == KeyState::KeyRelease || lastButtons[gamepad][i] == KeyState::KeyNone))
					gamepads[gamepad].buttons[i] = KeyState::KeyNone;
				else
					if (gamepads[gamepad].buttons[i] == KeyState::KeyPress && (lastButtons[gamepad][i] == KeyState::KeyPress || lastButtons[gamepad][i] == KeyState::KeyHold))
						gamepads[gamepad].buttons[i] = KeyState::KeyHold;
				lastButtons[gamepad][i] = gamepads[gamepad].buttons[i];
			}
		}
		else
		{
			memset(gamepads + gamepad, 0, sizeof(Gamepad));
		}
	}


	static KeyState lastState[(int)Key::MAX_KEY] = {};
	for (int i = 0; i < (int)Key::MAX_KEY; i++)
	{
		if (keys[i] == KeyState::KeyRelease &&  lastState[i] == KeyState::KeyRelease)
			keys[i] = KeyState::KeyNone;
		else
			if (keys[i] == KeyState::KeyPress && lastState[i] == KeyState::KeyPress)
				keys[i] = KeyState::KeyHold;
		lastState[i] = keys[i];
	}
}

void Input::SetMousePos(float x, float y)
{
	Input::MouseX = x;
	Input::MouseY = y;
}
KeyState Input::GetGamepadButton(uint32_t gamepad, GamepadButton button)
{
	assert(gamepad < 4);
	return gamepads[gamepad].buttons[(int)button];
}

float Input::GetGamepadAxis(uint32_t gamepad, GamepadAxis axis)
{
	assert(gamepad < 4);
	return gamepads[gamepad].axes[(int)axis];
}

glm::vec2 Input::GetMousePos()
{
	return { Input::MouseX, Input::MouseY };
}

KeyState Input::GetGamepadButton(GamepadButton button)
{
	return gamepads[0].buttons[(int)button];
}

uint32_t Input::GetActiveGamepadsCount()
{
	return activeGamepads;
}

float Input::GetGamepadAxis(GamepadAxis axis)
{
	return gamepads[0].axes[(int)axis];
}

