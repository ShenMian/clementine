// Copyright 2021 SMS
// License(Apache-2.0)

#ifndef CLEM_SCENE_ENTITY_H_
#define CLEM_SCENE_ENTITY_H_

#include "Clem/Log.h"
#include "Scene.h"
#include "entt.hpp"

class Scene;

/**
 * @addtogroup Scene
 * @{
 */

/**
 * 实体. 组件的容器.
 */
class Entity
{
public:
	Entity() = default;
	Entity(entt::entity id, Scene* scene);

	/**
	 * @brief 添加指定组件.
	 */
	template <typename T, typename... Args>
	void addComponent(Args&&... args);

	/**
	 * @brief 移除指定组件.
	 */
	template <typename T>
	void removeComponent();

	/**
	 * @brief 获取指定组件.
	 */
	template <typename T>
	T& getComponent();

	/**
	 * @brief 是否存在指定组件.
	 */
	template <typename T>
	bool hasComponent();

	entt::entity getId() const;
	Scene*      getScene() const;

private:
	entt::entity id    = entt::null;
	Scene*      scene = nullptr;
};

/**
 * end of Scene group
 * @}
 */

template <typename T, typename... Args>
void Entity::addComponent(Args&&... args)
{
	if(hasComponent<T>())
	{
		CLEM_CORE_ERROR("add a an existing component");
		return;
	}
	scene->registry.emplace<T>(id, std::forward<Args>(args)...);
}

template <typename T>
void Entity::removeComponent()
{
	if(!hasComponent<T>())
	{
		CLEM_CORE_ERROR("remove a nonexistent component");
		return;
	}
	scene->registry.get<T>(id);
}

template <typename T>
T& Entity::getComponent()
{
	if(!hasComponent<T>())
	{
		CLEM_CORE_CRITICAL("get a nonexistent component");
		abort();
	}
	return scene->registry.get<T>(id);
}

template <typename T>
bool Entity::hasComponent()
{
	return scene->registry.has<T>(id);
}

#endif // !CLEM_SCENE_ENTITY_H_
