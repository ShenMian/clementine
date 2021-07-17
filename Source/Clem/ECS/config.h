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

static_assert(std::is_integral<id_type>::value, "id_type must be integral.");
static_assert(std::is_integral<version_type>::value, "version_type must be integral.");

constexpr size_t chunkAlignment = 64;
constexpr size_t chunkSize      = 16 * 1024;

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

inline TypeIndex TypeRegistry::size = 0;

#	define CLEM_DECLARE_TYPE \
	public:                   \
		static ::clem::detal::TypeRegistry __type_registry;

#	define CLEM_DEFINE_TYPE(T) inline ::clem::detal::TypeRegistry T::__type_registry;

} // namespace detal

template <typename T>
TypeIndex Typeid()
{
	return T::__type_registry.index;
}

#endif

} // namespace clem
