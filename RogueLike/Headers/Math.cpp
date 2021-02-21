#include "Math.h"

float lerp(float a, float b, float t)
{
	return a + t * (b - a);
}

bool RayVsRect(const glm::vec2& rayOrigin, const glm::vec2& rayDir, const Transform& target, glm::vec2& contactPoint, glm::vec2& contactNormal, float& tHitNear)
{
	glm::vec2 tNear = (target.pos - rayOrigin) / rayDir;
	glm::vec2 tFar = (target.pos + target.size - rayOrigin) / rayDir;

	if (std::isnan(tNear.x) || std::isnan(tNear.y)) return false;
	if (std::isnan(tFar.x) || std::isnan(tFar.y)) return false;

	if (tNear.x > tFar.x) std::swap(tNear.x, tFar.x);
	if (tNear.y > tFar.y) std::swap(tNear.y, tFar.y);

	if (tNear.x > tFar.y || tNear.y > tFar.x) return false;

	tHitNear = std::max(tNear.x, tNear.y);
	float tHitFar = std::min(tFar.x, tFar.y);

	if (tHitFar < 0) return false;

	contactPoint = rayOrigin + tHitNear * rayDir;

	if (tNear.x > tNear.y)
		if (rayDir.x < 0)
		{
			contactNormal = { 1,0 };
		}
		else
			contactNormal = { -1,0 };
	else if (tNear.x < tNear.y)
		if (rayDir.y < 0)
			contactNormal = { 0,1 };
		else
			contactNormal = { 0,-1 };

	return true;
}

bool RectVsRect(const Transform& in, const Velocity& inVel, const Transform& target, glm::vec2& contactPoint, glm::vec2& contactNormal, float& contactTime)
{
	if (inVel.v.x == 0 && inVel.v.y == 0)
		return false;
	Transform expanded;
	expanded.pos = target.pos - in.size;
	expanded.size = target.size + in.size;
	if (RayVsRect(in.pos, inVel.v * Time::DeltaTime(), expanded, contactPoint, contactNormal, contactTime))
	{
		if (contactTime <= 1.0f && contactTime >= 0.0f)
			return true;
	}
	return false;
}

glm::vec2 CardinalToVec2(CardinalDir dir)
{

	switch (dir)
	{
	case CardinalDir::N:
		return glm::vec2( 0, 1);
	case CardinalDir::S:
		return glm::vec2( 0,-1);
	case CardinalDir::E:
		return glm::vec2( 1, 0);
	case CardinalDir::W:
		return glm::vec2(-1, 0);
	case CardinalDir::NE:
		return glm::vec2( 1, 1);
	case CardinalDir::NW:
		return glm::vec2(-1, 1);
	case CardinalDir::SE:
		return glm::vec2( 1,-1);
	case CardinalDir::SW:
		return glm::vec2(-1,-1);
	default:
		return glm::vec2(0, 0);
	}

}
