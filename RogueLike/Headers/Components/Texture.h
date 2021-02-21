#include <Tabasco/EntityManager.h>
#include "Headers/Sprite.h"

struct Texture
{
	Texture()
		:textureID(0)
	{}

	Texture(uint32_t textureID)
		:textureID(textureID)
	{
	}
	uint32_t textureID;
};