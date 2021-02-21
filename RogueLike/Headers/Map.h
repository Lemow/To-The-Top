#pragma once
#include <vector>
#include <iostream>
#include <glm/glm.hpp>
#include "Random.h"
#include "Math.h"

enum class Tile : char
{
	None = -1, Grass, Tree, Player
};


glm::uvec2 RandomDir();

struct Map
{

	Map()
		:sizeX(0),
		sizeY(0),
		tiles()
	{}

	Map(uint64_t x, uint64_t y)
		:sizeX(x),
		sizeY(y)
	{
		tiles.resize(x * y);
		for (Tile& t : tiles)
		{
			t = Tile::None;
		}
	}

	void Resize(size_t x, size_t y)
	{
		tiles.resize(x * y);
		sizeX = x;
		sizeY = y;
		memset(tiles.data(), (int)Tile::None, tiles.size() * sizeof(Tile));
	}

	auto operator[](size_t index)
	{
		//std::cout << index * sizeX << '\n';
		return tiles.begin() + index * sizeX;
	}

	const auto operator[](size_t index) const
	{
		//std::cout << index * sizeX << '\n';
		return tiles.begin() + index * sizeX;
	}

	size_t size() const
	{
		return tiles.size();
	}

	auto begin()
	{
		return tiles.begin();
	}

	auto end()
	{
		return tiles.end();
	}
	void clear()
	{
		for (auto& tile : tiles)
			tile = Tile::None;
	}

	uint32_t sizeX, sizeY;
	std::vector<Tile> tiles;

};

Map GenTestMap();
Map GenRoom(uint32_t startX, uint32_t startY,uint32_t sizeX, uint32_t sizeY);

void RenderMap(const Map& map);

Map GenMap(uint32_t sizeX, uint32_t sizeY);