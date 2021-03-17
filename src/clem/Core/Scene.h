// Copyright 2021 SMS
// License(Apache-2.0)

#ifndef CLEM_CORE_SCENE_H_
#define CLEM_CORE_SCENE_H_

#include "entt.hpp"

class NEntity;

/**
 * @addtogroup Core
 * @{
 */

/**
 * 场景. 创建并管理实体.
 */
class NScene
{
public:
	NEntity createEntity();
	void    destoryEntity(NEntity);

	void update(long dt);
	void render(long dt);

private:
	entt::registry registry;

	friend class NEntity;
};

/**
 * end of Core group
 * @}
 */

#endif // !CLEM_CORE_SCENE_H_
