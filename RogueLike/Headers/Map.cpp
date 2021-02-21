#include "Map.h"
#include <iostream>

struct Walker
{

	Walker(const glm::uvec2& pos, const glm::uvec2& dir)
		:pos(pos),
		dir(dir)
	{
	}

	Walker(const glm::uvec2& pos)
		:pos(pos),
		dir(RandomDir())
	{}

	Walker(uint32_t x, uint32_t y)
		:pos(x, y),
		dir(RandomDir())
	{}
	glm::uvec2 pos;
	glm::uvec2 dir;
};



glm::uvec2 RandomDir()

{
	int dir = Random::UInt(3);
	switch (dir)
	{
	case 0: // N
		return {  0,  1 };
	case 1: // E
		return {  1,  0 };
	case 2: // S
		return {  0, -1 };
	case 3: // W
		return { -1, 0 };
	}
}


void InsertRoom(Map& map, Map room, const glm::uvec2& ULCorner)
{
	for (int i = 0; i < room.sizeY; i++)
	{
		for (int j = 0; j < room.sizeX; j++)
		{
			map[i + ULCorner.y][j + ULCorner.x] = room[i][j];
		}
	}
}

Map GenTestMap()
{
	Map retval(25, 25);

	
	for (int i = 0; i < retval.sizeY; i++)
	{
		retval[i][0] = Tile::Tree;
		retval[i][retval.sizeX - 1] = Tile::Tree;
	}
	for (int j = 0; j < retval.sizeX; j++)
	{
		retval[0][j] = Tile::Tree;
		retval[retval.sizeY - 1][j] = Tile::Tree;
	}

	for(int i = 1; i < retval.sizeY - 1; i++)
		for (int j = 1; j < retval.sizeX - 1; j++)
		{
			retval[i][j] = Tile::Grass;
		}
	return retval;
}

Map GenRoom(uint32_t startX, uint32_t startY, uint32_t sizeX, uint32_t sizeY)
{
	constexpr float walkerDirChangeChance = 0.5f;
	constexpr float walkerSpawnChance = 0.05f;
	constexpr float walkerDestroyChance = 0.05f;
	constexpr int maxWalkers = 10;
	constexpr float percentToFill = 0.5f;

	uint32_t floorCount = 0;
	uint32_t minX = sizeX + 1, maxX = 0;
	uint32_t minY = sizeY + 1, maxY = 0;
	std::vector<Walker> walkers;
	walkers.emplace_back(startX,startY);
	Walker& startWalker = walkers.back();

	Map map(sizeX, sizeY);
	map[startWalker.pos.y][startWalker.pos.x] = Tile::Grass;
	if (startWalker.pos.y == 0)
	{
		startWalker.pos.y++;
	}
	else if (startWalker.pos.y == sizeY - 1)
	{
		startWalker.pos.y--;
	}

	map[startWalker.pos.y][startWalker.pos.x] = Tile::Grass;

	if (startWalker.pos.x == 0)
	{
		startWalker.pos.x++;
	} 
	else if(startWalker.pos.x == sizeX-1)
	{
		startWalker.pos.x--;
	}

	while((float)floorCount / (float)map.size() <= percentToFill)
	{
		for (const Walker& walker : walkers)
		{
			floorCount += map[walker.pos.y][walker.pos.x] == Tile::None;
			map[walker.pos.y][walker.pos.x] = Tile::Grass;
		}
		for (Walker& walker : walkers)
		{
			walker.pos.x += walker.dir.x;
			walker.pos.y += walker.dir.y;
			
			if (walker.pos.x < 1)
				walker.pos.x = 1;
			else if (walker.pos.x > map.sizeX - 2)
				walker.pos.x = map.sizeX - 2;

			if (walker.pos.y < 1)
				walker.pos.y = 1;
			else if (walker.pos.y > map.sizeY - 2)
				walker.pos.y = map.sizeY - 2;


			if (minX > walker.pos.x)
				minX = walker.pos.x;

			if (minY > walker.pos.y)
				minY = walker.pos.y;

			if (maxX < walker.pos.x)
				maxX = walker.pos.x;

			if (maxY < walker.pos.y)
				maxY = walker.pos.y;
		}
		for (int i = walkers.size() - 1; i >= 0; i--)
		{
			if ((Random::Float() < walkerDestroyChance) && walkers.size() > 1)
			{
				walkers.erase(walkers.begin() + i);
			}
		}
		for (Walker& walker : walkers)
		{
			if (Random::Float() < walkerSpawnChance && walkers.size() < maxWalkers)
			{
				walkers.emplace_back(walker.pos.x,walker.pos.y);
				break;
			}
		}

		for (Walker& walker : walkers)
		{
			if (Random::Float() < walkerDirChangeChance)
				walker.dir = RandomDir();
		}

	}
	for (int i = 0; i < map.sizeY; i++)
	{
		for (int j = 0; j < map.sizeX; j++)
		{
			if (map[i][j] != Tile::Grass)
				continue;

			if(i < map.sizeY - 1)
					if (map[i + 1][j] == Tile::None)
						map[i + 1][j] = Tile::Tree;

				if(i > 0)
					if (map[i - 1][j] == Tile::None)
						map[i - 1][j] = Tile::Tree;

				if(j < map.sizeX - 1)
					if (map[i][j + 1] == Tile::None)
						map[i][j + 1] = Tile::Tree;

				if(j > 0)
					if (map[i][j - 1] == Tile::None)
						map[i][j - 1] = Tile::Tree;
		}
	}

	/*uint32_t x = Random::UInt(1, map.sizeX - 2);
	uint32_t y = Random::UInt(1, map.sizeY - 2);

	while (map[y][x] != Tile::Grass)
	{
		x = Random::UInt(1, map.sizeX - 2);
		y = Random::UInt(1, map.sizeY - 2);
	}
	map[y][x] = Tile::Player;

	Map newMap(++maxX - (--minX) + 1, ++maxY - (--minY) + 1);

	for (int i = minY; i <= maxY; i++)
	{
		for (int j = minX; j <= maxX; j++)
		{
			newMap[i - minY][j - minX] = map[i][j];
		}
	}

	map = std::move(newMap);*/
	return map;
}

void RenderMap(const Map& map)
{
	system("cls");
	std::string frameBuffer;
	frameBuffer.reserve(map.size());

	for (int i = 0; i < map.sizeY; i++)
	{
		for (int j = 0; j < map.sizeX; j++)
		{
			frameBuffer.push_back(' ');
			switch (map[i][j])
			{
			case Tile::Grass:
				frameBuffer.push_back(' ');
				break;

			case Tile::Tree:
				frameBuffer.push_back('T');
				break;
			default:
				frameBuffer.push_back(',');
				break;
			}
		}
			frameBuffer.push_back('\n');
	}
	std::cout << frameBuffer;
}

struct SpaceNode
{
	SpaceNode(uint32_t sizeX, uint32_t sizeY, uint32_t cornerX, uint32_t cornerY)
		:sizeX(sizeX), sizeY(sizeY),
		cornerX(cornerX), cornerY(cornerY)
	{}

	uint32_t sizeX, sizeY;
	uint32_t cornerX, cornerY;
};

using NodeIt = std::vector<SpaceNode>::iterator;

void SplitV(std::vector<SpaceNode>& v, NodeIt& ptr)
{
	float ratio = Random::Float(0.3f, 0.7f);
	uint32_t ptrCornerX = ptr->cornerX;
	uint32_t ptrSizeX = ptr->sizeX;
	uint32_t lSizeY = static_cast<float>(ptr->sizeY) * ratio;
	uint32_t rSizeY = ptr->sizeY - lSizeY + 1;

	uint32_t lCornerY = ptr->cornerY;
	uint32_t rCornerY = lCornerY + lSizeY - 1;

	*ptr = SpaceNode(ptrSizeX,lSizeY, ptrCornerX, lCornerY);
	//ptr->left = (v.end() - 1)._Ptr;
	v.emplace_back(ptrSizeX,rSizeY, ptrCornerX, rCornerY);
	//ptr->right = (v.end() - 1)._Ptr;
}

void SplitH(std::vector<SpaceNode>& v, NodeIt& ptr)
{

	float ratio = Random::Float(0.3f, 0.7f);
	uint32_t ptrSizeY = ptr->sizeY;
	uint32_t ptrCornerY = ptr->cornerY;
	uint32_t lSizeX = static_cast<float>(ptr->sizeX) * ratio;
	uint32_t rSizeX = ptr->sizeX - lSizeX + 1;

	uint32_t lCornerX = ptr->cornerX;
	uint32_t rCornerX = lCornerX + lSizeX - 1;

	*ptr = SpaceNode(lSizeX, ptrSizeY, lCornerX, ptrCornerY);
//	ptr->left = (v.end() - 1)._Ptr;
	v.emplace_back(rSizeX, ptrSizeY, rCornerX, ptrCornerY);
//	ptr->right = (v.end() - 1)._Ptr;
}

Map GenMap(uint32_t sizeX, uint32_t sizeY)
{
	constexpr uint32_t roomSize = 35;
	const uint32_t maxIterations = std::min(sizeX / 20, sizeY / 20);

	std::vector<SpaceNode> nodes;
	nodes.reserve(1025);
	nodes.emplace_back(sizeX,sizeY,0,0);
	auto iter = nodes.begin();
	while(iter != nodes.end())
	{
		if (iter->sizeX <= roomSize && iter->sizeY <= roomSize)
		{
			iter++;
			continue;
		}

		if (iter->sizeX <= roomSize)
		{
			if (iter->sizeY > roomSize)
			SplitV(nodes, iter);
		}
		else if (iter->sizeY <= roomSize)
		{
			SplitH(nodes, iter);
		}
		else if(Random::UInt() % 2 == 0)
		{
			SplitH(nodes, iter);
		}
		else
		{
			SplitV(nodes, iter);
		}
	}
	
	Map retval(sizeX, sizeY);
	for (SpaceNode& node : nodes)
	{
		
		for (int i = node.cornerY; i < node.sizeY + node.cornerY; i++)
		{
			for (int j = node.cornerX; j < node.sizeX + node.cornerX; j++)
			{
				if (i == 0 || i == retval.sizeY - 1 || j == 0 || j == retval.sizeX - 1)
					retval[i][j] = Tile::Tree;
				else 
				{
					if (i == node.cornerY || i == node.cornerY + node.sizeY - 1 || j == node.cornerX || j == node.sizeX + node.cornerX)
					{
						retval[i][j] = Tile::Grass;
					}
				}
			}
		}
		if (node.cornerX > 0)
			node.cornerX++;
		if (node.cornerY > 0)
			node.cornerY++;

		if (node.cornerX + node.sizeX >= retval.sizeX || node.cornerX == 0)
			node.sizeX--;
		else
			node.sizeX -= 2;
		if (node.cornerY + node.sizeY >= retval.sizeY || node.cornerY == 0)
			node.sizeY--;
		else
			node.sizeY -= 2;

		bool allowed[4] = { 1,1,1,1 };
		int max = 4;
		if (node.cornerX == 0)
		{
			allowed[(int)CardinalDir::W] = 0;
			max--;
		}
		if (node.cornerY == 0)
		{
			allowed[(int)CardinalDir::S] = 0;
			max--;
		}
		if (node.cornerY + node.sizeY == retval.sizeY)
		{
			allowed[(int)CardinalDir::N] = 0;
			max--;
		}
		if (node.cornerX + node.sizeX == retval.sizeX)
		{
			allowed[(int)CardinalDir::E] = 0;
			max--;
		}
		CardinalDir dir = (CardinalDir)Random::UInt(max-1);
		int index = -1;
		int actual = -1;
		while (actual != (int)dir)
		{
			index++;
			if (allowed[index])
				actual++;
		}
		dir = (CardinalDir)index;

		uint32_t startX, startY;
		switch (dir)
		{
		case CardinalDir::N:
			startX = Random::UInt(1, node.sizeX- 2);
			startY = node.sizeY - 1;
			break;
		case CardinalDir::S:
			startX = Random::UInt(1, node.sizeX - 2);
			startY = 0;
			break;
		case CardinalDir::E:
			startX = node.sizeX - 1;
			startY = Random::UInt(1, node.sizeY - 2);
			break;
		case CardinalDir::W:
			startX = 0;
			startY = Random::UInt(1, node.sizeY  - 2);
			break;
		default:
			startX = node.sizeX  - 1;
			startY = Random::UInt(1, node.sizeY  - 2);
			break;
		}
		
		InsertRoom(retval, GenRoom(startX, startY, node.sizeX, node.sizeY), { node.cornerX,node.cornerY });
	}

	for (int i = 1; i < sizeY - 1; i++)
	{
		for (int j = 1; j < sizeX - 1; j++)
		{
			if (retval[i][j] == Tile::Grass)
			{
				if (retval[i + 1][j] == Tile::None)
					retval[i + 1][j] = Tile::Tree;

				if (retval[i - 1][j] == Tile::None)
					retval[i - 1][j] = Tile::Tree;

				if (retval[i][j + 1] == Tile::None)
					retval[i][j + 1] = Tile::Tree;

				if (retval[i][j - 1] == Tile::None)
					retval[i][j - 1] = Tile::Tree;
			}
		}
	}

	uint32_t x = Random::UInt(1,sizeX - 1);
	uint32_t y = Random::UInt(1,sizeY - 1);

	while (retval[y][x] != Tile::Grass)
	{
		x = Random::UInt(1, sizeX - 1);
		y = Random::UInt(1, sizeY - 1);
	}

	retval[y][x] = Tile::Player; // TODO: Better player spawning
	return retval;
}
