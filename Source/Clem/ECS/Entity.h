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
	 * @brief 构造函数.
	 */
	Entity(id_type id, version_type version, Registry& reg);

	/**
	 * @brief 添加组件.
	 */
	template <typename Com, typename... Args>
	Com& emplace(Args&&... args);

	/**
	 * @brief 移除组件.
	 */
	template <typename Com>
	void remove();

	/**
	 * @brief 获取组件.
	 */
	template <typename Com>
	Com& get() const;

	/**
	 * @brief 检查是否有指定的多个组件.
	 */
	template <typename... Coms>
	bool has() const;

	/**
	 * @brief 检查是否有效.
	 */
	bool isValid() const;

	const id_type id;

	const version_type version;

	bool operator==(const Entity& rhs) const;
	bool operator<(const Entity& rhs) const;

private:
	Registry& registry;
};

} // namespace clem

#include "Entity.inl"
