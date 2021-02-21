#pragma once
#include <glm/glm.hpp>

enum class KeyState : char
{
	KeyRelease, KeyPress, KeyHold, KeyNone
};

enum class Key
{
	LeftMB,
	RightMB,
	MiddleMB,
	W,
	A,
	S,
	D,
	SPACE,
	E,
	MAX_KEY
};
enum class GamepadButton
{
	A,B,X,Y,
	LB,RB,
	Select,Start,
	L3,R3,
	Up,Right,Down,Left
};
enum class GamepadAxis
{
	LeftX,LeftY,
	RightX,RightY,
	LT,RT
};

struct Gamepad
{
	KeyState buttons[14];
	float axes[6];
};

class Input
{
public:

	static void ScanKeys();
	static KeyState GetKey(Key key);
	static float GetGamepadAxis(GamepadAxis axis);
	static float GetGamepadAxis(uint32_t gamepad, GamepadAxis axis);
	static KeyState GetGamepadButton(GamepadButton button);
	static KeyState GetGamepadButton(uint32_t gamepad, GamepadButton button);
	static uint32_t GetActiveGamepadsCount();
	static void SetKey(Key key, KeyState state);
	static void SetMousePos(float x, float y);
	static glm::vec2 GetMousePos();

private:
	static KeyState keys[(int)Key::MAX_KEY];
	static Gamepad gamepads[4];
	static uint32_t activeGamepads;
	static float MouseX, MouseY;
};