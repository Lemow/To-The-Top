#pragma once
#include "Container.h"
#include "Serializer.h"
#include "Iterate.h"
#include "Entity.h"
#include <cassert>
#include <iostream>

constexpr uint32_t EntitiesPerRow = 256;

class Registry
{

	template<typename Component>
	using Container = Container<Component, EntitiesPerRow,true>;

public:

		Registry()
			:nextEntity(0),
			nextComponent(0)
		{
		}

		// TODO: improve this
		entity_t Create()
		{
			entity_t entity = entity_traits::enabledMask;

			entity |= nextEntity++;

			return entity;
		}

		void Destroy(entity_t entity)
		{
			if(entity_traits::enabledMask & entity)
				for (auto& set : pools)
				{
					set->erase(entity);
				}
		}

		template<typename Component>
		void Declare()
		{
			assure<Component>();
		}

		template<typename Component, typename... Args>
		Component& Emplace(entity_t entity, Args&&... args)
		{

			uint32_t id = comp_info::id<Component>(nextComponent);
			assure<Component>();

			Container<Component>& cont = *static_cast<Container<Component>*>(pools[id].get());

			cont.emplace(entity,std::forward<Args>(args)...);
			return cont.back();
		}

		template<typename Component>
		Component& GetComponent(entity_t entity)
		{
			assure<Component>();
			uint32_t index = comp_info::id<Component>(nextComponent);

			Container<Component>& cont = *static_cast<Container<Component>*>(pools[index].get());

			assert(cont.find(entity) != cont.end());

			return *cont.find(entity);
		}

		template<typename Component>
		bool HasComponent(entity_t entity)
		{
			assure<Component>();

			Container<Component>& cont = getContainer<Component>();
			return cont.contains(entity);
		}

		template<typename Component>
		void Erase(entity_t entity)
		{
			uint32_t index = comp_info::id<Component>(nextComponent);

			Container<Component>& cont = *static_cast<Container<Component>*>(pools[index].get());

			cont.erase(entity);
		}

		template<typename Component>
		IterateView<Component> Iterate()
		{
			assure<Component>();
			uint32_t index = comp_info::id<Component>(nextComponent);

			Container<Component>& cont = *static_cast<Container<Component>*>(pools[index].get());

			return IterateView<Component>( cont.get_sparse_set_packed());
		}

		template<typename First, typename ... Components>
		bool HasComponents(entity_t entity)
		{
			if constexpr (sizeof...(Components) > 0)
				return HasComponent<First>(entity) & HasComponents<Components...>(entity);
			else
				return HasComponent<First>(entity);
		}


		template<typename Component>
		void ShrinkToFit()
		{
			Container<Component>& cont = getContainer<Component>();
			cont.shrink_to_fit();
		}

		void Serialize(std::string_view filePath)
		{
			serializer.StartWrite(filePath);
			for (auto& pool : pools)
			{
				serializer.WriteComponents<256>(*pool);
			}
			serializer.EndWrite();
		}

		void Deserialize(std::string_view filePath)
		{
			serializer.StartRead(filePath);

			for(auto& pool : pools)
				serializer.ReadToContainer<256>(*pool);

			serializer.EndRead();
		}

		void Clear()
		{
			pools.clear();
		}

	private:

		template<typename Component>
		void assure()
		{
			uint32_t id = comp_info::id<Component>(nextComponent);
			if (pools.size() <= id)
			{
				pools.resize(id + 1);
				pools[id].reset(new Container<Component>);
			}
		}
		
		template<typename Component>
		Container<Component>& getContainer()
		{
			assure<Component>();
			uint32_t index = comp_info::id<Component>(nextComponent);

			return { *static_cast<Container<Component>*>(pools[index].get()) };
		}

		std::vector<Scope<SparseSet<EntitiesPerRow>>> pools;
		Serializer serializer;
	//	SparseSet<entity_t> entities;
		uint32_t nextEntity;
		uint32_t nextComponent;
};