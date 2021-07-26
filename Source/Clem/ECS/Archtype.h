// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "config.h"
#include <cstddef>
#include <set>
#include <typeindex>

namespace clem
{

struct Chunk;

class Archtype
{
public:
	Archtype() = default;

	Archtype(std::set<TypeIndex>&&);

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

	bool operator==(const Archtype& rhs) const;
	bool operator<(const Archtype& rhs) const;

	// size_t hashCode() const;

private:
	std::set<TypeIndex> types;
};

template <typename... Ts>
inline Archtype makeArchtype()
{
	return Archtype(std::move({Typeid<Ts>()...}));
}

} // namespace clem

#include "Archtype.inl"
