// Copyright 2021 SMS
// License(Apache-2.0)

#ifndef CLEM_SCENE_ENTITY_H_
#define CLEM_SCENE_ENTITY_H_

#include "Clem/Log.h"
#include "Clem/Math/Vec2.h"
#include "Scene.h"
#include "entt.hpp"

class Scene;

/**
 * @addtogroup Scene
 * @{
 */

typedef entt::entity entity_id;

/**
 * @brief 实体. 组件的容器.
 */
class Entity
{
public:
	Entity() = default;
	Entity(entity_id id, Scene* scene);

	/**
	 * @brief 添加指定组件.
	 */
	template <typename T, typename... Args>
	T& addComponent(Args&&... args);

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

	entity_id getId() const;
	Scene*    getScene() const;

	operator bool() const;
	operator entity_id() const;

private:
	entity_id id    = entt::null;
	Scene*    scene = nullptr;
};

/**
 * end of Scene group
 * @}
 */

template <typename T, typename... Args>
T& Entity::addComponent(Args&&... args)
{
	if(hasComponent<T>())
		CLEM_CORE_CRITICAL("add a an existing component");
	return scene->registry.emplace<T>(id, std::forward<Args>(args)...);
}

template <typename T>
void Entity::removeComponent()
{
	if(!hasComponent<T>())
		CLEM_CORE_CRITICAL("remove a nonexistent component");
	scene->registry.destroy<T>(id);
}

template <typename T>
T& Entity::getComponent()
{
	if(!hasComponent<T>())
		CLEM_CORE_CRITICAL("get a nonexistent component");
	return scene->registry.get<T>(id);
}

template <typename T>
bool Entity::hasComponent()
{
	return scene->registry.has<T>(id);
}

#endif // !CLEM_SCENE_ENTITY_H_
