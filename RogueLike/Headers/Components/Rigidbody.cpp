#include "Rigidbody.h"
#include "Headers/Transform.h"
#include "Velocity.h"
#include <algorithm>
#include <limits>
#include "Headers/Time.h"
#include "Headers/EntityManager.h"
#include "Headers/Math.h"

bool ResolveCollision(Transform& in, Velocity& inVel, Transform& target)
{
	glm::vec2 cPoint, cNormal;
	float cTime = 0.0f;
	if (RectVsRect(in, inVel, target, cPoint, cNormal, cTime))
	{
		inVel.v += cNormal * glm::vec2{std::abs(inVel.v.x), std::abs(inVel.v.y)};
		return true;
	}
	return false;
}

void CollisionSystem(EntityManager& em)
{
	auto iter = em.Iterate<Rigidbody>();
	std::vector<std::pair<entity_t, float>> z;
	z.reserve(iter.size() - 1);
	for (auto actor = iter.begin(); actor != iter.end(); actor++)
	{
		Rigidbody& actorRB = em.GetComponent<Rigidbody>(*actor);
		if (actorRB.type != Rigidbody::Dynamic)
			continue;
		z.clear();
		Transform& actorTransform = em.GetComponent<Transform>(*actor);
		Velocity& actorVel = em.GetComponent<Velocity>(*actor);
		
		for (auto acted = actor + 1; acted != iter.end(); acted++)
		{
			Rigidbody& actedRB = em.GetComponent<Rigidbody>(*acted);
				Transform& actedTransform = em.GetComponent<Transform>(*acted);
				glm::vec2 contactPoint, normals;
				float collisionTime = 0.0f;
				
				if (RectVsRect(actorTransform, actorVel, actedTransform, contactPoint, normals, collisionTime))
				{
					z.emplace_back(*acted, collisionTime);
				}
		}
		std::sort(z.begin(), z.end(), [](const std::pair<entity_t, float>& a, const std::pair<entity_t, float>& b)
			{
				return a.second < b.second;
			});

		for (auto j : z)
			ResolveCollision(actorTransform, actorVel, em.GetComponent<Transform>(j.first));
	}

}

void TriggerDetection(EntityManager& em)
{
}
