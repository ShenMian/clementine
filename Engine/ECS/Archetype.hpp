// Copyright 2021 ShenMian
// License(Apache-2.0)

#pragma once

#include <bitset>
#include <typeinfo>
#include <set>
#include <unordered_map>
#include "TypeIndex.hpp"

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

	bool anyOf(const Archetype& other) const noexcept
	{
		return (signature & other.signature).any();
	}

	bool allOf(const Archetype& other) const noexcept
	{
		return (signature & other.signature) == signature;
	}

	bool noneOf(const Archetype& other) const noexcept
	{
		return !anyOf(other);
	}

private:
	std::bitset<max_component_size> signature;

	inline static std::unordered_map<TypeIndex, size_t> index;
};

}
