#pragma once
#include "Entity.h"
#include <vector>
#include <sstream>

	template<size_t ePerRow = 256>
	class SparseSet
	{
	public:

		using index_type = uint32_t;
		using row_type = Scope<entity_t[]>;

		SparseSet()
			:erasedCount(0)
		{
		}
		virtual ~SparseSet() {};
		virtual void serialize(std::vector<char>& dest, std::stringstream& metadata) const = 0;

		virtual void deserialize(const std::vector<char>& readBuffer) = 0;

		index_type row(entity_t entity)
		{
			return static_cast<index_type>((entity & entity_traits::idMask) / ePerRow);
		}

		index_type column(entity_t entity)
		{
			return static_cast<index_type>(entity & (ePerRow - 1));
		}

		entity_t find(entity_t entity)
		{

			index_type index = assure(entity)[column(entity)];

			if (entity != packed[index])
				return 0;

			return index | entity_traits::enabledMask;
		}

		void emplace(entity_t entity)
		{
			assure(entity);

			if (contains(entity))
			{
				return;
			}

			sparse[row(entity)][column(entity)] = packed.size();
			packed.push_back(entity);
		}

		void recalculate_sparse_vector()
		{
			for (entity_t e : packed)
			{
				assure(e);
				sparse[row(e)][column(e)] = e;
			}
		}

		template<typename PackedIt>
		void swap(PackedIt a, PackedIt b)
		{
			SPC_CORE_ASSERT(a < packed.end() && b < packed.end(), "Packed iterator out of bounds while swapping!");

			entity_t aux = *a;
			entity_t& aRef = *sparse[row(*a)][column(*a)];
			entity_t& bRef = *sparse[row(*b)][column(*b)];

			*a = *b;
			*b = aux;

			aux = aRef;

			aRef = bRef;
			bRef = aux;

		}

		void ss_erase(entity_t entity)
		{	
			entity_t temp = packed.back();
			index_type delIndex = sparse[row(entity)][column(entity)];

			packed[delIndex] = temp;
			sparse[row(temp)][column(temp)] = delIndex;

			packed.pop_back();
		}

		virtual void erase(entity_t entity) = 0;

		size_t size() const noexcept
		{
			return packed.size();
		}

		void clear() noexcept
		{
			packed.clear();
			sparse.clear();
		}

		/// <summary>
		/// Moves all disabled entities to the end of packed then removes them
		/// </summary>
		void shrink_to_fit()
		{
			auto firstZero = packed.begin();

			for (auto e = packed.begin(); e != packed.end(); e++)
			{
				if (!((*e) & entity_traits::enabledMask))
				{
					firstZero = e;
					break;
				}
			}

			auto firstIt = firstZero;

			for (auto e = firstZero + 1 ; e < packed.end(); e++)
			{
				if (((*e) & entity_traits::enabledMask))
				{
					std::swap(*e, *firstZero);
					firstZero++;
				}
			}

			packed.resize(firstZero - packed.begin() + 1);

			for (; firstIt < packed.end(); firstIt++)
			{
				sparse[row(*firstIt)][column(*firstIt)] = *firstIt;
			}

			packed.shrink_to_fit();
			sparse.shrink_to_fit();
		}

		void packed_assure(index_type index)
		{
			if (index < packed.size())
				return;
			size_t oldSize = packed.size();
			packed.resize(index + 1);

			for (auto v = packed.begin() + oldSize; v != packed.end(); v++)
			{
				*v = 0;
			}
		}

		//assures no errors with indexing
		row_type& assure(entity_t entity)
		{
			index_type _row = row(entity);

			if (_row >= sparse.size())
			{
				sparse.resize(((uint32_t)entity & entity_traits::idMask) + 1);
			}

			if (!sparse[_row])
			{
				sparse[_row].reset(new entity_t[ePerRow]);
				for (auto it = sparse[_row].get(); it < sparse[_row].get() + ePerRow; it++)
				{
					*it = 0;
				}
			}

			return sparse[_row];
		}

		bool contains(entity_t entity)
		{
			index_type index = assure(entity)[column(entity)];

			if (packed.size() <= index)
				return false;

			return packed[index] == entity;
		}

		auto begin() { return packed.begin(); }
		auto end()   { return packed.end();   }

	protected:
		std::vector<entity_t> packed;
		std::vector<Scope<entity_t[]>> sparse;
		uint32_t erasedCount;
	};
