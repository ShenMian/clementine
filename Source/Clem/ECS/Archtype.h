// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <set>
#include <typeindex>
#include <typeinfo>

namespace clem
{
class Chunk;

template <typename...>
class Archtype
{
};

template <typename T, typename... Types>
class Archtype<T, Types...> : private Archtype<Types...>
{
public:
	Archtype();

	bool all(const Archtype&) const;
	bool any(const Archtype&) const;
	bool none(const Archtype&) const;

	bool operator==(const Archtype& rhs) const;
	bool operator<(const Archtype& rhs) const;

private:
	std::type_index           type;
	std::set<std::type_index> types;
};

template <>
class Archtype<>
{
};

template <typename T, typename... Types>
inline Archtype<T, Types...>::Archtype()
		: type(typeid(T))
{
	types += type + Archtype<Types...>::types;
}
} // namespace clem
