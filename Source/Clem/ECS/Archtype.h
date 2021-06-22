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

	size_t getHashCode() const;

private:
	std::set<std::type_index> types;
};

template <typename... Ts>
inline Archtype makeArchtype()
{
	return Archtype(std::move({std::type_index(typeid(Ts))...}));
}

template <typename T, typename... Ts>
inline bool Archtype::all() const
{
	if constexpr(sizeof...(Ts) > 0)
		return types.find(typeid(T)) != types.end() && all<Ts...>();
	else
		return types.find(typeid(T)) != types.end();
}

template <typename T, typename... Ts>
inline bool Archtype::any() const
{
	if constexpr(sizeof...(Ts) > 0)
		return types.find(typeid(T)) != types.end() || any<Ts...>();
	else
		return types.find(typeid(T)) != types.end();
}

template <typename... Ts>
inline bool Archtype::none() const
{
	return !any<Ts...>();
}

template <typename T>
inline Archtype& Archtype::add()
{
	types.insert(typeid(T));
	return *this;
}

template <typename T>
inline Archtype& Archtype::remove()
{
	types.erase(typeid(T));
	return *this;
}
} // namespace clem

/*
template <>
struct std::hash<clem::Archtype>
{
	size_t operator()(const clem::Archtype& v) const noexcept
	{
		return v.getHashCode();
	}
};

template <>
struct std::equal_to<clem::Archtype>
{
	bool operator()(const clem::Archtype& lhs, const clem::Archtype& rhs) const
	{
		return lhs == rhs;
	}
};
*/
