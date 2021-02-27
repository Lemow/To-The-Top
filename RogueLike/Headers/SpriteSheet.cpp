#include "SpriteSheet.h"
#include <GL/glew.h>



SpriteSheet::SpriteSheet(std::string_view fPath, uint32_t spriteSizeX, uint32_t spriteSizeY)
	:m_sprite(fPath, spriteSizeX, spriteSizeY, &m_spriteCount)
{
}

SpriteSheet::SpriteSheet(SpriteSheet&& other) noexcept
	:m_sprite(std::move(other.m_sprite)),
	m_spriteCount(other.m_spriteCount)
{
}

glm::vec2 SpriteSheet::GetSpriteCoords(uint32_t x, uint32_t y) const 
{
	return { (float)x / m_spriteCount.x, 1.0f - (float)y / m_spriteCount.y };
}

glm::vec2 SpriteSheet::GetSpriteCoords(uint32_t spriteID) const
{
	uint32_t x = spriteID % (uint32_t)m_spriteCount.x;
	uint32_t y = spriteID / (uint32_t)m_spriteCount.x;
	return GetSpriteCoords(x,y);
}

glm::vec2 SpriteSheet::GetSpriteSize() const
{
	return glm::vec2(1.0f / (float)m_spriteCount.x, 1.0f/ (float)m_spriteCount.y);
}

void SpriteSheet::Bind()
{
	m_sprite.Bind();
}
