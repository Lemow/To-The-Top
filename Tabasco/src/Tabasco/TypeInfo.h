#pragma once
	namespace comp_info
	{


		static uint32_t next(uint32_t& original)
		{
			return original++;
		}


		template<typename Component>
		uint32_t id(uint32_t& original)
		{
			static const uint32_t ID = next(original);
			return ID;
		}


	}