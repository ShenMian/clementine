// Copyright 2021 SMS
// License(Apache-2.0)

#ifndef CLEM_SCENE_ENTITY_H_
#define CLEM_SCENE_ENTITY_H_

#include "Clem/Component/Tag.h"
#include "Clem/Core/Math/Math.h"
#include "Clem/Log.h"
#include "Scene.h"
#include "entt/entt.hpp"

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

private:
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
		CLEM_CORE_FATAL("add a an existing component '{}' to entity '{}'", typeid(Com).name(), getComponent<Tag>().tag);
	return scene->registry.emplace<Com>(id, std::forward<Args>(args)...);
}

template <typename Com>
void Entity::removeComponent()
{
	if(!hasComponent<Com>())
		CLEM_CORE_FATAL("remove a nonexistent component '{}' from entity '{}'", typeid(Com).name(), getComponent<Tag>().tag);
	scene->registry.destroy<Com>(id);
}

template <typename Com>
Com& Entity::getComponent()
{
	if(!hasComponent<Com>())
		CLEM_CORE_FATAL("get a nonexistent component '{}' from entity '{}'", typeid(Com).name(), getComponent<Tag>().tag);
	return scene->registry.get<Com>(id);
}

template <typename Com>
bool Entity::hasComponent()
{
	return scene->registry.has<Com>(id);
}

#endif // !CLEM_SCENE_ENTITY_H_
