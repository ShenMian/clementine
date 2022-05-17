// Copyright 2021 ShenMian
// License(Apache-2.0)

#pragma once

#include <vector>
#include <numeric>
#include "Archetype.hpp"
#include "Entity.hpp"

namespace ecs
{

constexpr size_t max_entity_size = 5000;

/**
 * @brief 实体管理器.
 */
class Registry
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
	 */
	bool valid(const Entity& entity) const noexcept;

private:
	Entity::id_type request();
	void recycle(Entity::id_type id);

	std::vector<Entity> entities_;
	std::vector<Entity::id_type> freeIds_;
};

static_assert(std::numeric_limits<Entity::id_type>::max() < std::numeric_limits<size_t>::max());

}
