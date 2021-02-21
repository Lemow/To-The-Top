#pragma once
#include "Headers/EntityManager.h"
#include "Headers/Components/Player.h"
#include "Headers/Components/Item.h"

void ItemPickupSystem(Entity& playerEntity, EntityManager& em, Player& player);

