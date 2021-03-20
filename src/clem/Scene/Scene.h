// Copyright 2021 SMS
// License(Apache-2.0)

#ifndef CLEM_SCENE_SCENE_H_
#define CLEM_SCENE_SCENE_H_

#include "entt.hpp"

typedef entt::entity entity_id;
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
	Entity createEntity();
	Entity getEntity(entity_id id);
	void   destoryEntity(Entity);

	void update(float dt);
	void render(float dt);

private:
	entt::registry registry;

	friend class Entity;
};

/**
 * end of Scene group
 * @}
 */

#endif // !CLEM_SCENE_SCENE_H_
