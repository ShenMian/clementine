// Copyright 2022 ShenMian
// License(Apache-2.0)

#pragma once

#include "archetype.hpp"
#include "entity.hpp"
#include <numeric>
#include <vector>

namespace ecs
{

constexpr size_t max_entity_size = 5000;

/**
 * @brief 实体管理器.
 */
class Manager
{
public:
	/**
	 * @brief 创建实体.
	 */
	Entity create();

	/**
	 * @brief 销毁实体.
	 *
	 * @param entity 要销毁的实体.
	 */
	void destroy(const Entity& entity);

	/**
	 * @brief 判断实体是否有效.
	 * 
	 * 被销毁的实体会失效.
	 */
	bool valid(const Entity& entity) const noexcept;

	template <typename T>
	T& add_component(const Entity& entity)
	{
		archetypes_[entity.id()] += Archetype(Typeid<T>());
		return arrays_[Typeid<T>()][entity.id()];
	}

	template <typename T>
	void remove_component(const Entity& entity)
	{
		archetypes_[entity.id()] -= Archetype(Typeid<T>());
		arrays_[Typeid<T>()].remove(entity.id());
	}

private:
	Entity::id_type allocate_id();
	void            deallocate_id(Entity::id_type id);

	std::vector<Entity>          entities_;
	std::vector<Entity::id_type> freeIds_;
	std::vector<Archetype>       archetypes_;

	std::unordered_map<TypeIndex, Array> arrays_;
};

static_assert(std::numeric_limits<Entity::id_type>::max() < std::numeric_limits<size_t>::max());

} // namespace ecs

#include "manager.inl"
