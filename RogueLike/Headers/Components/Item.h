#pragma once
#include <memory>
#include "Headers/EntityManager.h"


struct Item
{
	Item()
		:OnEquip(nullptr),
		OnHit(nullptr),
		OnGetHit(nullptr)
	{}

	Item(void(*OnEquip)(EntityManager& em, entity_t player), 
		void(*OnHit)(EntityManager& em, entity_t player, entity_t hit) = nullptr, 
		void(*OnGetHit)(EntityManager& em, entity_t player, entity_t hit) = nullptr)
		:OnEquip(OnEquip),
		OnHit(OnHit),
		OnGetHit(OnGetHit)
	{
	}

	void(*OnEquip)(EntityManager& em, entity_t player);
	void(*OnHit)(EntityManager& em, entity_t player, entity_t hit);
	void(*OnGetHit)(EntityManager& em, entity_t player, entity_t hit);
};

