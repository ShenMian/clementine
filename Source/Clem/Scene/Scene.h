// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "entt/entt.hpp"
#include <string>
#include <unordered_map>
#include <cstdint>

namespace clem
{
class Entity;

/**
 * @addtogroup Scene
 * @{
 */

/**
 * @brief 场景. 创建并管理实体.
 */
class Scene
{
public:
	/**
	 * @brief 创建新的实体.
	 *
	 * @param tag 新实体的标签.
	 */
	Entity createEntity(const std::string& tag = "");

	/**
	 * @brief 通过标签获取实体.
	 *
	 * @param tag 要获取的实体的标签.
	 */
	Entity getEntity(const std::string_view& tag);

	/**
	 * @brief 通过标签销毁实体.
	 *
	 * @param tag 要销毁的实体的标签.
	 */
	void destroyEntity(const std::string_view& tag);

	void update(float dt);
	void render(float dt);

private:
	void updateScripts(float dt);
	void updateRigidbodies(float dt);
	void renderSprites();
	void sortSprites();

	entt::registry registry;

	friend class Entity;
};

/**
 * end of Scene group
 * @}
 */
} // namespace clem
