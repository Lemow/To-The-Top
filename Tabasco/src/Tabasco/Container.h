#pragma once
#include "SparseSet.h"
#include <cassert>
#include <cstring>

	template<typename Component, size_t ePerRow, bool serializable>
	class Container : public SparseSet<ePerRow>
	{

	public:

		void serialize(std::vector<char>& Dest, std::stringstream& metadata) const override
		{
			if constexpr (serializable)
			{
				size_t oldSize = Dest.size();
				size_t vecSize = components.size();
				const std::vector<entity_t>& packed = get_sparse_set_packed();
				if (vecSize == 0)
					return;

				assert(vecSize == packed.size());

				Dest.resize(Dest.size() + vecSize * sizeof(Component) + packed.size() * sizeof(entity_t));

				char* writer = &*Dest.begin() + oldSize;
				memcpy(writer, components.data(), components.size() * sizeof(Component));
				writer += components.size() * sizeof(Component);
				memcpy(writer, packed.data(), packed.size() * sizeof(entity_t));

				metadata << typeid(Component).name() << ":";
				metadata.write((const char*)&oldSize, sizeof(size_t));
				metadata.write((const char*)&vecSize, sizeof(size_t));
			}

		}

		void deserialize(const std::vector<char>& readBuffer) override
		{


			union sptb
			{
				int64_t pos;
				std::byte buffer[8];
			}offset, size;


			std::string comp = typeid(Component).name();
			comp.append(":");
			size_t bufferPos = -1;
			for (size_t i = comp.size(); i < readBuffer.size(); i++)
			{
				bool ok = true;
				for (int j = 0; j < comp.size(); j++)
				{
					if (comp[j] != readBuffer[i + j - comp.size()])
					{
						ok = false;
						break;
					}
				}
				if (ok)
					bufferPos = i;
			}



#ifdef SPC_PLATFORM_WINDOWS
			__unaligned int64_t* reader = (__unaligned int64_t*)(readBuffer.data() + bufferPos);
			offset.pos = *reader;
			reader++;
			size.pos = *reader;
#else
			std::byte* reader = (std::byte*)(readBuffer.data() + bufferPos);

			for (int i = 0; i < 8; i++, reader++)
			{
				offset.buffer[i] = *reader;
			}

			for (int i = 0; i < 8; i++, reader++)
			{
				size.buffer[i] = *reader;
			}
#endif
			const std::byte* Src = (std::byte*)readBuffer.data() + offset.pos;
			size_t count = size.pos;

			clear();

			std::vector<entity_t>& packed = get_sparse_set_packed();

			packed.resize(count);
			components.resize(count);

			memcpy(components.data(), Src, count * sizeof(Component));
			Src += size.pos * sizeof(Component);
			memcpy(packed.data(), Src, count * sizeof(entity_t));

			recalculate_sparse_vector();
		}

		void erase(entity_t entity) override
		{
			entity_t found = SparseSet<ePerRow>::find(entity);
			if (found & entity_traits::enabledMask)
			{
				uint32_t index = found & entity_traits::idMask;

				components[index] = components.back();

				components.pop_back();
				SparseSet<ePerRow>::ss_erase(entity);
			}
		}

		template<typename ... Args>
		void emplace(entity_t entity, Args&& ... args)
		{
			SparseSet<ePerRow>::emplace(entity);
			components.emplace_back(std::forward<Args>(args)...);
		}

		Component& back()
		{
			return components.back();
		}

		void clear()
		{
			components.clear();
			SparseSet<ePerRow>::clear();
		}

		bool contains(entity_t entity)
		{
			return SparseSet<ePerRow>::contains(entity);
		}

		auto find(entity_t entity)
		{
			entity_t found = SparseSet<ePerRow>::find(entity);

			if (!found)
				return components.end();

			return components.begin() + (found & entity_traits::idMask);
		}

		void recalculate_sparse_vector()
		{
			SparseSet<ePerRow>::recalculate_sparse_vector();
		}

		void shrink_to_fit()
		{
			SparseSet<ePerRow>::shrink_to_fit();
			components.shrink_to_fit();
		}

		size_t size() const
		{
			return components.size();
		}

		auto begin() const { return components.begin(); }
		auto end() const { return components.end(); }

		std::vector<entity_t>& get_sparse_set_packed()
		{
			return SparseSet<ePerRow>::packed;
		}

		const std::vector<entity_t>& get_sparse_set_packed() const
		{
			return SparseSet<ePerRow>::packed;
		}
		
		const std::vector<Component>& get_component_vector() const
		{
			return components;
		}

		std::vector<Component>& get_component_vector()
		{
			return components;
		}

	private:
		std::vector<Component> components;
	};