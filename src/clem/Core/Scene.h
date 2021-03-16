// Copyright 2021 SMS
// License(Apache-2.0)

#ifndef CLEM_CORE_SCENE_H_
#define CLEM_CORE_SCENE_H_

#include "entt.hpp"

class NEntity;

/**
 * ����. ����������ʵ��.
 */
class NScene
{
public:
	NEntity createEntity();
	void    destoryEntity(NEntity);

private:
	entt::registry registry;

	friend class NEntity;
};

#endif // !CLEM_CORE_SCENE_H_
