// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Clem/Scene/Entity.h"

namespace clem
{
/**
 * @brief 组件.
 */
class Component
{
public:
	/**
	 * @brief 设置所属的实体.
	 *
	 * @param entity 所属的实体;
	 */
	void setEntity(const Entity& entity);

	/**
	 * @brief 获取所属的实体.
	 */
	Entity& getEntity();

private:
	Entity entity;
};
} // namespace clem
