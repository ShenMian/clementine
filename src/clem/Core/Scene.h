// Copyright 2021 SMS
// License(Apache-2.0)

#ifndef CLEM_CORE_SCENE
#define CLEM_CORE_SCENE

#include "entt.hpp"

class NEntity;

class NScene
{
public:
	NEntity& createEntity();
	void     destoryEntity(const NEntity&);

private:
	entt::registry registry;
};

#endif // !CLEM_CORE_SCENE
