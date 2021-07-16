// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "config.h"
#include <cassert>

namespace clem
{

class Registry;

class Entity
{
public:
	/**
	 * @brief 默认构造函数.
	 */
	Entity() = default;

	/**
	 * @brief 构造函数.
	 */
	Entity(id_type id, version_type version, Registry& reg);

	/**
	 * @brief 添加组件.
	 * 
	 * @tparam T 组件.
	 */
	template <typename T, typename... Args>
	T& add(Args&&... args);

	/**
	 * @brief 移除组件.
	 * 
	 * @tparam T 组件.
	 */
	template <typename T>
	void remove();

	/**
	 * @brief 获取组件.
	 * 
	 * @tparam T 组件.
	 */
	template <typename T>
	T& get() const;

	/**
	 * @brief 判断是否有指定的全部组件.
	 * 
	 * @param entity 要检测的实体.
	 * @tparam Ts 组件列表.
	 */
	template <typename... Ts>
	bool allOf() const;

	/**
	 * @brief 判断是否有指定的任意组件.
	 * 
	 * @param entity 要检测的实体.
	 * @tparam Ts 组件列表.
	 */
	template <typename... Ts>
	bool anyOf() const;

	/**
	 * @brief 判断是否没有指定的任何组件.
	 * 
	 * @param entity 要检测的实体.
	 * @tparam Ts 组件列表.
	 */
	template <typename... Ts>
	bool noneOf() const;

	/**
	 * @brief 检查实体是否有效.
	 */
	bool valid() const;

	id_type id() const;

	version_type version() const;

	bool operator==(const Entity& rhs) const;
	bool operator<(const Entity& rhs) const;
	Entity& operator=(const Entity& rhs);

private:
	id_type      id_      = 0;
	version_type version_ = 0;
	Registry*    registry = nullptr;
};

} // namespace clem

#include "Entity.inl"
