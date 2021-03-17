// Copyright 2021 SMS
// License(Apache-2.0)

#ifndef CLEM_CORE_SCENE_H_
#define CLEM_CORE_SCENE_H_

#include "entt.hpp"

class Entity;

/**
 * @addtogroup Core
 * @{
 */

/**
 * 场景. 创建并管理实体.
 */
class Scene
{
public:
	Entity createEntity();
	void   destoryEntity(Entity);

	void update(long dt);
	void render(long dt);

private:
	entt::registry registry;

	friend class Entity;
};

/**
 * end of Core group
 * @}
 */

#endif // !CLEM_CORE_SCENE_H_
