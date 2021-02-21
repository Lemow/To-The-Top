#pragma once
#include <memory>
#include "Math.h"

struct Animation
{
	// Frame per Second
	float speed;
	// TextureIDs
	uint32_t startID, finID;


};

enum class AnimationType : unsigned char
{
	PlayerIdle,
	MAX_INDEX
};

class AnimationManager
{
public:
	static void Init();

	static std::pair<uint32_t, TimePoint>StartAnimation(AnimationType type);
	static uint32_t ContinueAnimation(AnimationType type, TimePoint startPoint);
	static const Animation& GetAnimation(AnimationType type);
private:
	static Animation animations[(int)AnimationType::MAX_INDEX];
};