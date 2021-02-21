#pragma once
#include "Headers/EntityManager.h"

struct Interactable
{
	Interactable()
		:interaction(nullptr)
	{
	}

	Interactable(void(*interaction)(EntityManager& em, entity_t thisID))
		:interaction(interaction)
	{}

	void(*interaction)(EntityManager& em, entity_t thisID);
};