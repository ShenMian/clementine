// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Clem/Core/Math/Math.h"
#include "Clem/Logger.h"
#include "Scene.h"
#include "entt/entt.hpp"

namespace clem
{
class Component;

/**
 * @addtogroup Scene
 * @{
 */

/**
 * @brief 实体. 组件的容器.
 */
class Entity
{
public:
	typedef entt::entity id_t;

	Entity() = default;
	Entity(id_t id, Scene* scene);

	/**
	 * @brief 添加指定组件.
	 */
	template <typename Com, typename... Args>
	Com& addComponent(Args&&... args);

	/**
	 * @brief 移除指定组件.
	 */
	template <typename Com>
	void removeComponent();

	/**
	 * @brief 获取指定组件.
	 */
	template <typename Com>
	Com& getComponent();

	/**
	 * @brief 是否存在指定组件.
	 */
	template <typename Com>
	bool hasComponent();

	id_t   getId() const;
	Scene* getScene() const;

	operator bool() const;
	operator id_t() const;

	bool operator==(const Entity&) const;
	bool operator!=(const Entity&) const;

private:
	void onAddComponent(Component*);

	id_t   id    = entt::null;
	Scene* scene = nullptr;
};

/**
 * end of Scene group
 * @}
 */

template <typename Com, typename... Args>
Com& Entity::addComponent(Args&&... args)
{
	if(hasComponent<Com>())
		CLEM_LOG_FATAL("core", "add a an existing component '{}' to entity '{}'", typeid(Com).name() /*, getComponent<Tag>().string*/);
	auto& com = scene->registry.emplace<Com>(id, std::forward<Args>(args)...);
	onAddComponent(dynamic_cast<Component*>(&com));
	return com;
}

template <typename Com>
void Entity::removeComponent()
{
	if(!hasComponent<Com>())
		CLEM_LOG_FATAL("core", "remove a nonexistent component '{}' from entity '{}'", typeid(Com).name() /*, getComponent<Tag>().string*/);
	scene->registry.remove<Com>(id);
}

template <typename Com>
Com& Entity::getComponent()
{
	if(!hasComponent<Com>())
		CLEM_LOG_FATAL("core", "get a nonexistent component '{}' from entity '{}'", typeid(Com).name()/*, getComponent<Tag>().string*/);
	return scene->registry.get<Com>(id);
}

template <typename Com>
bool Entity::hasComponent()
{
	return scene->registry.has<Com>(id);
}
} // namespace clem
