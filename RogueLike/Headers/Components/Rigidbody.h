#pragma once
#include <Tabasco/EntityManager.h>
#include "Headers/EntityManager.h"

struct Rigidbody
{
	enum RigidbodyType : char
	{
		Static, Kinematic, Dynamic
	}type;
	Rigidbody()
		:type(Static)
	{}
	Rigidbody(RigidbodyType type)
		:type(type)
	{}
};

struct Trigger
{
	void(*triggerFunc)(Registry&,entity_t);
};

void CollisionSystem(EntityManager& em);
void TriggerDetection(EntityManager& em);