// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <cstddef>
#include <cstdint>
#include <type_traits>
#include <typeindex>

namespace clem
{

using id_type      = uint32_t;
using version_type = uint16_t;

static_assert(std::is_integral<id_type>::value, "id_type must be integral.");
static_assert(std::is_integral<version_type>::value, "version_type must be integral.");

constexpr size_t chunk_alignment = 64;
constexpr size_t chunk_size      = 16 * 1024;

// #define CLEM_HAVE_RTTI

#ifdef CLEM_HAVE_RTTI

using TypeIndex = std::type_index;

#    define CLEM_DECLARE_TYPE
#    define CLEM_DEFINE_TYPE(type)

template <typename T>
TypeIndex Typeid()
{
    return typeid(T);
}

#else

class TypeIndex
{
public:
    TypeIndex(uint32_t id)
        : id(id)
    {
    }

    [[nodiscard]] size_t hash_code() const noexcept
    {
        return id;
    }

    [[nodiscard]] bool operator==(const TypeIndex& rhs) const noexcept
    {
        return id == rhs.id;
    }

    [[nodiscard]] bool operator<(const TypeIndex& rhs) const noexcept
    {
        return id < rhs.id;
    }

    [[nodiscard]] bool operator!=(const TypeIndex& rhs) const noexcept
    {
        return !(*this == rhs);
    }

    [[nodiscard]] bool operator>=(const TypeIndex& rhs) const noexcept
    {
        return !(*this < rhs);
    }

    [[nodiscard]] bool operator>(const TypeIndex& rhs) const noexcept
    {
        return rhs < *this;
    }

    [[nodiscard]] bool operator<=(const TypeIndex& rhs) const noexcept
    {
        return !(rhs < *this);
    }

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
    static uint32_t size;
};

inline uint32_t TypeRegistry::size = 0;

#    define CLEM_DECLARE_TYPE \
    public:                   \
        static ::clem::detal::TypeRegistry __type_registry;

#    define CLEM_DEFINE_TYPE(T) inline ::clem::detal::TypeRegistry T::__type_registry;

} // namespace detal

template <typename T>
TypeIndex Typeid()
{
    return T::__type_registry.index;
}

#endif

} // namespace clem

#ifndef CLEM_HAVE_RTTI

namespace std
{

template <>
struct hash<clem::TypeIndex>
{
    size_t operator()(const clem::TypeIndex& index) const
    {
        return index.hash_code();
    }
};

template <>
struct equal_to<clem::TypeIndex>
{
    size_t operator()(const clem::TypeIndex& lhs, const clem::TypeIndex& rhs) const
    {
        return lhs == rhs;
    }
};

}; // namespace std

#endif
