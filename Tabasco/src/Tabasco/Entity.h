#pragma once
#include <memory>

	template<typename T>
	using Scope = std::unique_ptr<T>;

	namespace entity_traits
	{
		static constexpr uint32_t idMask = uint32_t(-1) >> 1;
		static constexpr uint32_t enabledMask = ~idMask;
	}

	using entity_t = uint32_t;