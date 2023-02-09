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
	template <typename T, typename... Ts>
	static Archetype create()
	{
		if constexpr(sizeof...(Ts) > 0)
			return Archetype({Typeid<T>()}) + create<Ts...>();
		else
			return Archetype({Typeid<T>()});
	}

	Archetype() = default;
	Archetype(const std::initializer_list<TypeIndex>& types)
	{
		for(const auto& type : types)
		{
			if(!index_.contains(type))
				index_.insert({type, index_.size()});
			signature_.set(index_.at(type));
		}
	}

	bool any_of(const Archetype& other) const noexcept { return (signature_ & other.signature_).any(); }
	bool all_of(const Archetype& other) const noexcept { return (signature_ & other.signature_) == signature_; }
	bool none_of(const Archetype& other) const noexcept { return !any_of(other); }

	Archetype operator+(const Archetype& rhs) { return Archetype(*this) += rhs; }
	Archetype operator-(const Archetype& rhs) { return Archetype(*this) -= rhs; }

	Archetype& operator+=(const Archetype& rhs)
	{
		signature_ |= rhs.signature_;
		return *this;
	}
	Archetype& operator-=(const Archetype& rhs)
	{
		signature_ &= rhs.signature_;
		return *this;
	}

private:
	std::bitset<max_component_size> signature_;

	inline static std::unordered_map<TypeIndex, size_t> index_;
};

} // namespace ecs
