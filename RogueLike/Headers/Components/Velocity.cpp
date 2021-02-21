#include "Velocity.h"
#include "Headers/Transform.h"
#include "Headers/Time.h"
#include "Headers/Math.h"

void VelocitySystem(EntityManager& em)
{
	auto iter = em.Iterate<Velocity>();
	for (auto entity : iter)
	{
		Velocity& vel = em.GetComponent<Velocity>(entity);
		Transform& tr = em.GetComponent<Transform>(entity);
		
		tr.pos += vel.v * Time::DeltaTime();
		glm::vec2 delta = vel.tv - vel.v;
		if (abs(delta.x) <= 10.0f)
			vel.v.x = vel.tv.x;
		else
			vel.v.x = lerp(vel.v.x, vel.tv.x, Time::DeltaTime() * 10.0f);

		if (abs(delta.y) <= 10.0f)
			vel.v.y = vel.tv.y;
		else
			vel.v.y = lerp(vel.v.y, vel.tv.y, Time::DeltaTime() * 10.0f);

	}
}
