// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <set>
#include <typeindex>

namespace clem
{

struct Chunk;

class Archtype
{
public:
	Archtype() = default;

	Archtype(std::set<std::type_index>&&);

	template <typename T, typename... Ts>
	bool all() const;

	template <typename T, typename... Ts>
	bool any() const;

	template <typename... Ts>
	bool none() const;

	template <typename T>
	Archtype& add();

	template <typename T>
	Archtype& remove();

	bool operator==(const Archtype& rhs) const;
	bool operator<(const Archtype& rhs) const;

	size_t hashCode() const;

private:
	std::set<std::type_index> types;
};

template <typename... Ts>
inline Archtype makeArchtype()
{
	return Archtype(std::move({std::type_index(typeid(Ts))...}));
}

} // namespace clem

#include "Archtype.inl"
