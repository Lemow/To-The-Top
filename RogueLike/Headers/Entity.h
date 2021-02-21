#pragma once
#include <Tabasco/EntityManager.h>
#include <glm/glm.hpp>
#include "Components/Tag.h"
#include "Transform.h"

class Entity
{
public:
	friend class EntityManager;

	Entity();
	Entity(Registry* re, entity_t id);
	Entity(Registry* re);
	Entity(Registry* re, const glm::vec2& pos, Tag tag = Tag::None,const glm::vec2& size = {100,100});
	Entity(Entity&& other) noexcept;
	Entity& operator=(Entity&& other) noexcept;
	~Entity();
	Entity(const Entity& other) = delete;
	Entity& operator=(const Entity& other) = delete;
	bool operator==(entity_t other);
	template<typename Component>
	Component& GetComponent()
	{
		return re->GetComponent<Component>(entity);
	}
	template<typename Component, typename ... Args>
	Component& AddComponent(Args&& ... args)
	{
		return re->Emplace<Component>(entity,std::forward<Args>(args)...);
	}
	template<typename Component>
	bool HasComponent()
	{
		return re->HasComponent<Component>(entity);
	}
	template<typename Component>
	void RemoveComponent()
	{
		re->Erase<Component>(entity);
	}

	entity_t GetID()
	{
		return entity;
	}

	void SetParent(const Entity& other)
	{
		GetComponent<Transform>().parentID = other.entity;
	}

	void SetParent(entity_t parentID)
	{
		GetComponent<Transform>().parentID = parentID;
	}

	Tag& tag()
	{
		return GetComponent<Tag>();
	}

	Transform& transform()
	{
		return GetComponent<Transform>();
	}

private:
	Registry* re;
	entity_t entity;
};