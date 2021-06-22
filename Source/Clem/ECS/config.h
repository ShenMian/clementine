// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <cstddef>
#include <cstdint>
#include <typeindex>

namespace clem
{
using id_type      = uint32_t;
using version_type = uint16_t;

constexpr auto chunkAlignment = 64;
constexpr auto chunkSize      = 16 * 1024;

// #define CLEM_HAVE_RTTI

#ifdef CLEM_HAVE_RTTI

using TypeIndex = std::type_index;

#	define CLEM_DECLARE_TYPE
#	define CLEM_DEFINE_TYPE(type)

template <typename T>
TypeIndex Typeid()
{
	return typeid(T);
}

#else

using TypeIndex = uint32_t;

namespace detal
{
class TypeRegistry
{
public:
	TypeRegistry()
			: index(size)
	{
		size++;
	}

	const TypeIndex index;

private:
	static TypeIndex size;
};

#	define CLEM_DECLARE_TYPE \
	public:                   \
		detal::TypeRegistry __type_registry;
#	define CLEM_DEFINE_TYPE(type) detal::TypeRegistry type::__type_registry;

template <typename T>
TypeIndex Typeid()
{
	return T::__type_registry.index;
}
} // namespace detal

#endif
} // namespace clem
