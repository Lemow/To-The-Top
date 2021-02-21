#include "InteractSystem.h"
#include "Headers/Components/Peon.h"
#include "Headers/Math.h"
#include <algorithm>

void InteractSystem(Entity& player, EntityManager& em)
{
	

	Transform& playerTrans = player.transform();
	Peon& playerPeon = player.GetComponent<Peon>();
	glm::vec2 rayDir;
	glm::vec2 rayOrigin = playerTrans.pos + playerTrans.size / 2.0f;
	switch (playerPeon.orientation)
	{
	case CardinalDir::N:
		rayDir = {0, raySize};
		break;
	case CardinalDir::S:
		rayDir = {0, -raySize};
		break;
	case CardinalDir::E:
		rayDir = { raySize, 0 };
		break;
	case CardinalDir::W:
		rayDir = { -raySize, 0};
		break;
	case CardinalDir::NE:
		rayDir = { raySize * sqrt_2 / 2.0f,raySize * sqrt_2 / 2.0f};
		break;
	case CardinalDir::NW:
		rayDir = { -raySize * sqrt_2 / 2.0f,raySize * sqrt_2 / 2.0f };
		break;
	case CardinalDir::SE:
		rayDir = { raySize * sqrt_2 / 2.0f,-raySize * sqrt_2 / 2.0f };
		break;
	case CardinalDir::SW:
		rayDir = { -raySize * sqrt_2 / 2.0f,-raySize * sqrt_2 / 2.0f };
		break;
	default:
		return;
	}


	auto InterIter = em.Iterate<Interactable>();
	float minTime = std::numeric_limits<float>::infinity();
	entity_t minID = 0;
	for (entity_t inter : InterIter)
	{
		glm::vec2 dummy1, dummy2;
		float contact;
		if(RayVsRect(rayOrigin, rayDir, em.GetComponent<Transform>(inter),dummy1,dummy2,contact))
		{
			if (minTime > contact && contact <= 1.0f && contact >= 0.0f)
			{
				minTime = contact;
				minID = inter;
			}
		}
	}
	if(minID & entity_traits::enabledMask)
		em.GetComponent<Interactable>(minID).interaction(em, minID);

}
