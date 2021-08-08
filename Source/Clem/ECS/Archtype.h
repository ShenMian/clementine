// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "config.h"
#include <cstddef>
#include <functional>
#include <typeindex>
#include <unordered_set>

namespace clem
{

/**
 * @addtogroup ECS
 * @{
 */

struct Chunk;

/**
 * @brief 原型.
 */
class Archtype
{
public:
    Archtype() = default;

    Archtype(std::unordered_set<TypeIndex>&&);

    /**
	 * @brief 判断是否有指定的全部类型.
	 */
    template <typename T, typename... Ts>
    bool all() const;

    /**
	 * @brief 判断是否有指定的任意类型.
	 */
    template <typename T, typename... Ts>
    bool any() const;

    /**
	 * @brief 判断是否没有指定的任何类型.
	 */
    template <typename... Ts>
    bool none() const;

    /**
	 * @brief 添加类型.
	 */
    template <typename T>
    Archtype& add();

    /**
	 * @brief 移除类型.
	 */
    template <typename T>
    Archtype& remove();

    /**
	 * @brief 移除全部类型.
	 */
    void clear();

    size_t hashCode() const;

    auto operator<=>(const Archtype&) const = default;

private:
    std::unordered_set<TypeIndex> types;
};

template <typename... Ts>
inline Archtype makeArchtype()
{
    return Archtype(std::move({Typeid<Ts>()...}));
}

/**
 * end of ECS group
 * @}
 */

} // namespace clem

#include "Archtype.inl"