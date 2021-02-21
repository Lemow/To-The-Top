#pragma once
#include <chrono>

using TimePoint = std::chrono::time_point<std::chrono::steady_clock>;
using Duration = std::chrono::duration<float>;


class Time
{
public:
	static void Init();
	static void Step();
	static float DeltaTime();
	static TimePoint CurrentTime();
	static TimePoint LastTime();

	static float timeScale;
private:
	static std::chrono::time_point<std::chrono::steady_clock> now, last, before;
	static std::chrono::duration<float> duration;
	static float dt;
};