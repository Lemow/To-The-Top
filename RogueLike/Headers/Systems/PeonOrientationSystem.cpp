#include "PeonOrientationSystem.h"
#include "Headers/Components/Peon.h"
#include "Headers/Components/Texture.h"

void OrientationSystem(EntityManager& em)
{
	auto iter = em.Iterate<Peon>();
	for (entity_t ent : iter)
	{
		if (!em.HasComponent<Texture>(ent))
			continue;

		Peon& peon = em.GetComponent<Peon>(ent);
		Transform& tr = em.GetComponent<Transform>(ent);

		switch (peon.orientation)
		{
		case CardinalDir::NW:
		case CardinalDir::SW:
		case CardinalDir::W:
			tr.size.x = -std::abs(tr.size.x);
			break;
		case CardinalDir::SE:
		case CardinalDir::NE:
		case CardinalDir::E:
			tr.size.x = std::abs(tr.size.x);
			break;
		default:
			break;
		}
	}
}
