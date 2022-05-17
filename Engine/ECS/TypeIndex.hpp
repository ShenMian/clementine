// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <cstdint>
#include <xhash>

// #define CLEM_USE_RTTI

// TODO: 在有 RTTI 的情况下将包含 typeid 的实现隐藏到 TypeIndex 中, 而不是 Typeid

#ifdef CLEM_USE_RTTI

using TypeIndex = std::type_index;

#define DECLARE_TYPE

template <typename T>
TypeIndex Typeid()
{
	return typeid(T);
}

#else

class TypeIndex
{
public:
	constexpr TypeIndex(uint32_t id)
		: id(id)
	{
	}

	[[nodiscard]] constexpr size_t hash_code() const noexcept
	{
		return id;
	}

	auto operator<=>(const TypeIndex&) const = default;

private:
	uint32_t id;
};

namespace detal
{

class TypeRegistry
{
public:
	TypeRegistry()
		: index(size++)
	{
	}

	const TypeIndex index;

private:
	inline static uint32_t size = 0;
};

#define DECLARE_TYPE                                         \
    public:                                                  \
        inline static ::detal::TypeRegistry __type_registry;

} // namespace detal

template <typename T>
TypeIndex Typeid()
{
	return T::__type_registry.index;
}

#endif

#ifndef CLEM_USE_RTTI

namespace std
{

template <>
struct hash<TypeIndex>
{
	size_t operator()(const TypeIndex& index) const
	{
		return index.hash_code();
	}
};

}; // namespace std

#endif
