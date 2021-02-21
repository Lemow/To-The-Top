#pragma once
#include <glm/glm.hpp>
#include <chrono>
#include "Transform.h"
#include "Components/Velocity.h"
#include "Time.h"

constexpr float sqrt_2 = 1.414213562373095f;
constexpr float raySize = 275.0f;



enum class CardinalDir : char
{
	N, W, E, S,
	NW, NE,
	SW, SE,
	None
};

float lerp(float a, float b, float t);

bool RayVsRect(const glm::vec2& rayOrigin, const glm::vec2& rayDir, const Transform& target,
	glm::vec2& contactPoint, glm::vec2& contactNormal, float& tHitNear);

bool RectVsRect(const Transform& in, const Velocity& inVel, const Transform& target,
	glm::vec2& contactPoint, glm::vec2& contactNormal, float& contactTime);

glm::vec2 CardinalToVec2(CardinalDir dir);
