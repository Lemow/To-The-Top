#pragma once
#include <vector>
#include "Stats.h"
#include "Item.h"

struct Player
{
	Player() = default;

	Player(Stats& playerStats)
		:playerStats(playerStats)
	{
	}

	std::vector<Item> items;
//	std::vector<Weapon> weapons;
	Stats playerStats;
};