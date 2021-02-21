#pragma once
#include <Tabasco/EntityManager.h>
#include "Headers/EntityManager.h"
#include <glm/glm.hpp>

struct Velocity
{
	Velocity()
		:tv(0.0f,0.0f),
		v(0.0f,0.0f)
	{
	}
	Velocity(glm::vec2 tv, glm::vec2 v)
		:tv(tv),
		v(v)
	{}

	//target velocity
	glm::vec2 tv;
	//velocity
	glm::vec2 v;
};

void VelocitySystem(EntityManager& em);