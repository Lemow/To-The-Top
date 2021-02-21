#include "SpriteSheetManager.h"
#include "Renderer.h"

SpriteSheetManager::SpriteSheetManager()
{
}

SpriteSheetManager::SpriteSheetManager(std::vector<SpriteSheet> spriteSheets)
	:m_spriteSheets(std::move(spriteSheets))
{
	m_sheetSizes.reserve(m_spriteSheets.size());

	for (const auto& sheet : m_spriteSheets)
	{
		m_sheetSizes.push_back(sheet.m_spriteCount.x * sheet.m_spriteCount.y);
	}

	for (auto s = m_sheetSizes.begin()+1; s != m_sheetSizes.end(); s++)
	{
		*s += *(s - 1);
	}
}

void SpriteSheetManager::AddSpriteSheet(SpriteSheet spriteSheet)
{
	if(m_sheetSizes.size() > 0)
		m_sheetSizes.push_back((spriteSheet.m_spriteCount.x * spriteSheet.m_spriteCount.y) + m_sheetSizes.back());
	else
		m_sheetSizes.push_back(spriteSheet.m_spriteCount.x * spriteSheet.m_spriteCount.y);
	m_spriteSheets.emplace_back(std::move(spriteSheet));
}


void SpriteSheetManager::ClearSpriteSheets()
{
	m_spriteSheets.clear();
	m_sheetSizes.clear();
}

void SpriteSheetManager::ReserveSheets(uint32_t count)
{
	m_sheetSizes.reserve(count);
	m_spriteSheets.reserve(count);
}

glm::vec4 SpriteSheetManager::GetSprite(uint32_t spriteID, uint32_t* textureID)
{
	int last = 0;
	int index = 0;
	for (int size : m_sheetSizes)
	{
		if (spriteID >= last && spriteID < size)
		{
			spriteID -= last;
			break;
		}
		last = size;
		index++;
	}
	m_spriteSheets[index].Bind();

	*textureID = index;
	glm::vec2 corner = m_spriteSheets[index].GetSpriteCoords(spriteID);
	glm::vec2 size = m_spriteSheets[index].GetSpriteSize();

	return { corner,size };
}
