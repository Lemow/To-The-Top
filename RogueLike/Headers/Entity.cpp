#include "Entity.h"
#include "Headers/Components/Tag.h"
#include "Headers/Transform.h"
#include "Headers/EntityManager.h"

Entity::Entity()
	:re(nullptr),
	entity(0)
{
}

Entity::Entity(Registry* re, entity_t id)
	:re(re),
	entity(id)
{
}

Entity::Entity(Registry* re)
	:re(re),
	entity(re->Create())
{
	AddComponent<Tag>(Tag::None);
	AddComponent<Transform>();
}

Entity::Entity(Registry* re, const glm::vec2& pos, Tag tag, const glm::vec2& size)
	:re(re),
	entity(re->Create())
{
	AddComponent<Tag>(tag);
	AddComponent<Transform>(pos, size);
}

Entity::Entity(Entity&& other)noexcept
	:re(other.re),
	entity(other.entity)
{
	other.entity = 0;
}

Entity& Entity::operator=(Entity&& other)noexcept
{
	re->Destroy(entity);
	entity = other.entity;
	re = other.re;
	other.entity &= entity_traits::idMask;
	return *this;
}

bool Entity::operator==(entity_t other)
{
	return other == entity;
}

Entity::~Entity()
{
	if(re)
		re->Destroy(entity);
}
