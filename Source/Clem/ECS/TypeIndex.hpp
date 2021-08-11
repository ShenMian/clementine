// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <cstdint>
#include <xhash>

namespace clem
{

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

}; // namespace std

#endif