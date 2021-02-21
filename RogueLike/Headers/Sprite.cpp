#include "Sprite.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stb_image/stb_image.h>
#include <iostream>
#include "Renderer.h"

Sprite::Sprite(std::string_view fPath, uint32_t spriteSizeX, uint32_t spriteSizeY, glm::vec2* count)
{
	

	stbi_set_flip_vertically_on_load(true);

	int x, y, channels;
	uint8_t* image = stbi_load(fPath.data(), &x,&y,&channels, 0);

	glCreateTextures(GL_TEXTURE_2D, 1, &m_textureID);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	if (image)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,x,y,0,GL_RGBA, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);

		if (count)
		{
			count->x = x / spriteSizeX;
			count->y = y / spriteSizeY;
		}

	}
	else
	{
		std::cout << "Failed to load image!\n";
	}

	stbi_image_free(image);
}

Sprite::Sprite(Sprite&& other) noexcept
	:m_textureID(other.m_textureID)
{
	other.m_textureID = 0;
}

Sprite::~Sprite()
{
	glDeleteTextures(1, &m_textureID);
}

void Sprite::Bind()
{
	Renderer::BindTexture(m_textureID);
}
