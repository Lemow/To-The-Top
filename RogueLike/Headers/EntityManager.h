#pragma once
#include <Tabasco/EntityManager.h>
#include "Entity.h"
#include "Components/Tag.h"
#include "Transform.h"

class EntityManager
{
public:

	Entity Create();
	Entity Create(const glm::vec2& pos, Tag tag = Tag::None, const glm::vec2& size = { 100,100 });
	entity_t RegistryCreate();
	entity_t RegistryCreate(const glm::vec2& pos, Tag tag = Tag::None, const glm::vec2& size = { 100,100 });

	template<typename Component>
	Component& GetComponent(entity_t entity)
	{
		return re.GetComponent<Component>(entity);
	}

	template<typename Component>
	bool HasComponent(entity_t entity)
	{
		return re.HasComponent<Component>(entity);
	}

	template<typename ... Components>
	bool HasComponents(entity_t entity)
	{
		return re.HasComponents<Components ...>(entity);
	}

	template<typename Component, typename ... Args>
	void AddComponent(entity_t entity, Args&& ...  args)
	{
		re.Emplace<Component>(entity,std::forward<Args>(args) ... );
	}

	template<typename Component>
	void RemoveComponent(entity_t entity)
	{
		re.Erase<Component>(entity);
	}

	void Destroy(entity_t entity)
	{
		re.Destroy(entity);
	}

	template<typename Component>
	auto Iterate()
	{
		return re.Iterate<Component>();
	}


private:
	Registry re;
};

