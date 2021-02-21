#include "ItemPickupSystem.h"
#include "Headers/Math.h"
#include "Headers/Components/Peon.h"
#include <chrono>

void ItemPickupSystem(Entity& playerEntity, EntityManager& em, Player& player)
{

	auto items = em.Iterate<Item>();
	Transform& playerTrans = playerEntity.transform();
	Peon& playerPeon = playerEntity.GetComponent<Peon>();

	glm::vec2 rayOrigin = playerTrans.pos + playerTrans.size / 2.0f;

	float minTime = std::numeric_limits<float>::infinity();
	entity_t minID = 0;

	for (auto itemID : items)
	{
		Transform& itemTr = em.GetComponent<Transform>(itemID);
		glm::vec2 dummy1, dummy2;
		float contact;
		auto xd = raySize * CardinalToVec2(playerPeon.orientation);
		if (RayVsRect(rayOrigin, raySize * CardinalToVec2(playerPeon.orientation), itemTr,dummy1,dummy2,contact))
		{
			if (minTime > contact && contact <= 1.0f && contact >= 0.0f)
			{
				minTime = contact;
				minID = itemID;
			}
		}
	}
	if (minID == 0)
		return;

	Item& item = em.GetComponent<Item>(minID);
	player.items.push_back(item);
	em.Destroy(minID);
	player.items.back().OnEquip(em, playerEntity.GetID());
}
