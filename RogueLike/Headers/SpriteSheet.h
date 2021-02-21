#pragma once
#include "Sprite.h"
#include <glm/glm.hpp>

class SpriteSheet
{
public:
	friend class SpriteSheetManager;

	SpriteSheet(std::string_view fPath, uint32_t SpriteSizeX, uint32_t SpriteSizeY);
	SpriteSheet(const SpriteSheet& other) = delete;
	SpriteSheet(SpriteSheet&& other) noexcept;

	glm::vec2 GetSpriteCoords(uint32_t x, uint32_t y) const;
	glm::vec2 GetSpriteCoords(uint32_t spriteID) const;

	glm::vec2 GetSpriteSize() const;

	void Bind();

private:
	Sprite m_sprite;
	glm::vec2 m_spriteCount;
};