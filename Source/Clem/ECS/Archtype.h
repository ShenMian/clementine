// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <set>
#include <typeindex>
#include <typeinfo>

namespace clem
{
class Chunk;

class Archtype
{
public:
	Archtype(std::set<std::type_index>&&);

	template <typename T, typename... Args>
	bool all() const;

	template <typename T, typename... Args>
	bool any() const;

	template <typename... Args>
	bool none() const;

	bool operator==(const Archtype& rhs) const;
	bool operator<(const Archtype& rhs) const;

private:
	std::set<std::type_index> types;
};

template <typename... Types>
inline Archtype makeArchtype()
{
	return Archtype({std::type_index(typeid(Types))...});
}

template <typename T, typename... Args>
inline bool Archtype::all() const
{
	if constexpr(sizeof...(Args) > 0)
		return types.find(typeid(T)) != types.end() && all<Args...>();
	else
		return types.find(typeid(T)) != types.end();
}

template <typename T, typename... Args>
inline bool Archtype::any() const
{
	if constexpr(sizeof...(Args) > 0)
		return types.find(typeid(T)) != types.end() || any<Args...>();
	else
		return types.find(typeid(T)) != types.end();
}

template <typename... Args>
inline bool Archtype::none() const
{
	return !any<Args...>();
}
} // namespace clem
