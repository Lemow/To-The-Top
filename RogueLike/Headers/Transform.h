#pragma once
#include <glm/glm.hpp>
#include <Tabasco/Entity.h>


struct Transform
{
	Transform()
		:parentID(0)
		,pos(0.0f,0.0f),
		size(100.0f,100.0f)
	{}

	Transform(const glm::vec2& pos, const glm::vec2& size)
		:parentID(0),
		pos(pos),
		size(size)
	{}
	Transform(entity_t parentID,const glm::vec2& pos, const glm::vec2& size)
		:parentID(parentID),
		pos(pos),
		size(size)
	{}

	entity_t parentID;
	glm::vec2 pos;
	glm::vec2 size;
	
};