// Copyright 2022 ShenMian
// License(Apache-2.0)

#pragma once

#include "core/type_index.hpp"
#include <bitset>
#include <set>
#include <typeinfo>
#include <unordered_map>

namespace ecs
{

constexpr size_t max_component_size = 128;

/**
 * @brief 原型.
 */
class Archetype
{
public:
	Archetype(const std::initializer_list<TypeIndex>& types)
	{
		for(const auto& type : types)
		{
			if(!index.contains(type))
				index.insert({type, index.size()});
			signature.set(index.at(type));
		}
	}

	bool any_of(const Archetype& other) const noexcept { return (signature & other.signature).any(); }
	bool all_of(const Archetype& other) const noexcept { return (signature & other.signature) == signature; }
	bool none_of(const Archetype& other) const noexcept { return !any_of(other); }

	Archetype& operator+=(const Archetype& rhs)
	{
		signature |= rhs.signature;
		return *this;
	}
	Archetype& operator-=(const Archetype& rhs)
	{
		signature &= rhs.signature;
		return *this;
	}

private:
	std::bitset<max_component_size> signature;

	inline static std::unordered_map<TypeIndex, size_t> index;
};

} // namespace ecs
