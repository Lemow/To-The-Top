#pragma once
#include "SpriteSheet.h"
#include <vector>


class SpriteSheetManager
{
public:

	SpriteSheetManager();
	SpriteSheetManager(std::vector<SpriteSheet> spriteSheets);
	
	void AddSpriteSheet(SpriteSheet spriteSheet);
	void ClearSpriteSheets();
	void ReserveSheets(uint32_t count);

	glm::vec4 GetSprite(uint32_t spriteID, uint32_t* textureID);

private:
	std::vector<SpriteSheet> m_spriteSheets;
	std::vector<int> m_sheetSizes;
};