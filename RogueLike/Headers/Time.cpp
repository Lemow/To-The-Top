#include "Time.h"

TimePoint Time::last;
TimePoint Time::now;
TimePoint Time::before;
Duration Time::duration;
float Time::timeScale = 1.0f;
float Time::dt = 1.0f;

void Time::Init()
{
	Time::before = Time::last = std::chrono::high_resolution_clock::now();
}

float Time::DeltaTime()
{
	return dt;
}

void Time::Step()
{
	before = last;
	now = std::chrono::high_resolution_clock::now();
	duration = now - last;
	last = now;
	dt = duration.count() * timeScale;
}


TimePoint Time::CurrentTime()
{
	return now;
}

TimePoint Time::LastTime()
{
	return before;
}