// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "TypeIndex.hpp"
#include "config.h"
#include <any>
#include <array>
#include <cassert>
#include <map>
#include <typeindex>
#include <unordered_map>

namespace clem
{

/**
 * @addtogroup ECS
 * @{
 */

struct alignas(chunk_alignment) Chunk
{
public:
    template <typename T, typename... Args>
    T& addComponent(id_type id, Args&&... args);

    template <typename T>
    void removeComponent(id_type id);

    template <typename T>
    T& getComponent(id_type id);

    template <typename T>
    bool hasComponent(id_type id);

    size_t getSize() const;

    size_t getSizeBytes() const;

    bool empty() const;

private:
    size_t                            size;
    std::array<std::byte, chunk_size> buffer;

    std::unordered_map<id_type, std::unordered_map<TypeIndex, std::any>> components;
};

template <typename T, typename... Args>
inline T& Chunk::addComponent(id_type id, Args&&... args)
{
    components[id][Typeid<T>()] = T(args...); // 调用方错误: 构造函数重载不存在
    size++;
    return std::any_cast<T&>(components[id][Typeid<T>()]);
}

template <typename T>
inline void Chunk::removeComponent(id_type id)
{
    components[id][Typeid<T>()].reset();
    size--;
}

template <typename T>
[[nodiscard]] inline T& Chunk::getComponent(id_type id)
{
    assert(components[id][Typeid<T>()].has_value());
    return std::any_cast<T&>(components[id][Typeid<T>()]);
}

template <typename T>
[[nodiscard]] inline bool Chunk::hasComponent(id_type id)
{
    return components[id][Typeid<T>()].has_value();
}

/**
 * end of ECS group
 * @}
 */

} // namespace clem
