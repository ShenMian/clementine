// Copyright 2021 SMS
// License(Apache-2.0)

#ifndef CLEM_CORE_ENTITY_H_
#define CLEM_CORE_ENTITY_H_

#include "Scene.h"
#include "clem/log.h"
#include "entt.hpp"

class NScene;

/**
 * 实体. 组件的容器.
 */
class NEntity
{
public:
	NEntity() = default;
	NEntity(entt::entity id, NScene* scene);

	template <typename T, typename... Args>
	void addComponent(Args&&... args);

	template <typename T>
	void removeComponent();

	template <typename T>
	T& getComponent();

	template <typename T>
	bool hasComponent();

	entt::entity getId() const;
	NScene*      getScene() const;

private:
	entt::entity id    = entt::null;
	NScene*      scene = nullptr;
};

template <typename T, typename... Args>
void NEntity::addComponent(Args&&... args)
{
	if(hasComponent<T>())
	{
		CLEM_CORE_ERROR("add a an existing component");
		return;
	}
	scene->registry.emplace<T>(id, std::forward<Args>(args)...);
}

template <typename T>
void NEntity::removeComponent()
{
	if(!hasComponent<T>())
	{
		CLEM_CORE_ERROR("remove a nonexistent component");
		return;
	}
	scene->registry.get<T>(id);
}

template <typename T>
T& NEntity::getComponent()
{
	if(!hasComponent<T>())
	{
		CLEM_CORE_CRITICAL("get a nonexistent component");
		abort();
	}
	return scene->registry.get<T>(id);
}

template <typename T>
bool NEntity::hasComponent()
{
	return scene->registry.has<T>(id);
}

#endif // !CLEM_CORE_ENTITY_H_
