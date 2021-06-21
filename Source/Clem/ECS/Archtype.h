// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <set>
#include <typeindex>
#include <typeinfo>

namespace clem
{
class Chunk;

template <typename... Types>
class Archtype
{
public:
	template <typename T, typename... Args>
	bool all() const;

	template <typename T, typename... Args>
	bool any() const;

	template <typename... Args>
	bool none() const;

	bool operator<(const Archtype<Types...>& rhs) const;

private:
	std::set<std::type_index> types = {std::type_index(typeid(Types))...};
};

template <typename... Types>
template <typename T, typename... Args>
bool Archtype<Types...>::all() const
{
	if constexpr(sizeof...(Args) > 0)
		return types.find(typeid(T)) != types.end() && all<Args...>();
	else
		return types.find(typeid(T)) != types.end();
}

template <typename... Types>
template <typename T, typename... Args>
bool Archtype<Types...>::any() const
{
	if constexpr(sizeof...(Args) > 0)
		return types.find(typeid(T)) != types.end() || any<Args...>();
	else
		return types.find(typeid(T)) != types.end();
}

template <typename... Types>
template <typename... Args>
bool Archtype<Types...>::none() const
{
	return !any<Args...>();
}

template <typename... Types1, typename... Types2>
bool operator==(const Archtype<Types1...>& lhs, const Archtype<Types2...>& rhs) const
{
	return lhs.types == rhs.types;
}

template <typename... Types>
bool Archtype<Types...>::operator<(const Archtype<Types...>& rhs) const
{
	return types < rhs.types;
}
} // namespace clem
