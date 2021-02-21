#pragma once
#include <string_view>
#include <glm/glm.hpp>

class Sprite
{
public:
	Sprite() = default;
	Sprite(std::string_view fPath, uint32_t spriteSizeX, uint32_t spriteSizeY, glm::vec2* count = nullptr);
	Sprite(Sprite&& other) noexcept;
	~Sprite();
	void Bind();

private:
	uint32_t m_textureID;
};