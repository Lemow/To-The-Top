#pragma once
#include "SparseSet.h"
#include "Container.h"
#include "TypeInfo.h"
#include <vector>


	template<typename Component>

	class IterateView
	{
	public:

		IterateView(std::vector<entity_t>& ent)
			:ent(ent)
		{
		}
		auto begin() const
		{
			return ent.begin();
		}

		auto end() const
		{

			return ent.end();
		}

		size_t size() const
		{
			return ent.size();
		}

	private:
		std::vector<entity_t>& ent;
	};
