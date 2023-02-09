// Copyright 2022 ShenMian
// License(Apache-2.0)

#pragma once

#include "core/hash.hpp"
#include <cstdint>
#include <typeindex>

// TODO: 在有 RTTI 的情况下将包含 typeid 的实现隐藏到 TypeIndex 中, 而不是 Typeid

// #define CLEM_USE_RTTI

#ifdef CLEM_USE_RTTI

// using TypeIndex = std::type_index;

class TypeIndex
{
public:
	constexpr TypeIndex(std::type_index index) : index(index) {}

	constexpr size_t hash_code() const noexcept { index.hash_code() }

	auto operator<=>(const TypeIndex&) const = default;

private:
	std::type_index index;
};

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
	constexpr TypeIndex(uint32_t id) : id(id) {}

	constexpr size_t hash_code() const noexcept
	{
		size_t hash = 0;
		core::hash_combine(hash, id);
		return hash;
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
	TypeRegistry() : index(size++) {}

	const TypeIndex index;

private:
	inline static uint32_t size = 0;
};

	#define DECLARE_TYPE                                                                                               \
	public:                                                                                                            \
		inline static ::detal::TypeRegistry __type_registry;

} // namespace detal

template <typename T>
TypeIndex Typeid()
{
	return T::__type_registry.index;
}

#endif

MAKE_HASHABLE(TypeIndex, t.hash_code())
