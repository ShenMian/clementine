// Copyright 2022 ShenMian
// License(Apache-2.0)

#pragma once

#include "archetype.hpp"
#include "array.hpp"
#include "core/check.hpp"
#include "entity.hpp"
#include <memory>
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
		if(!arrays_.contains(Typeid<T>()))
			arrays_.insert({Typeid<T>(), std::make_shared<Array<T>>()});

		remove_from_group(archetypes_[entity.id()], entity);
		archetypes_[entity.id()] += Archetype::create<T>();
		add_to_group(archetypes_[entity.id()], entity);

		return (*get_array<T>())[entity.id()];
	}

	template <typename T>
	void remove_component(const Entity& entity)
	{
		remove_from_group(archetypes_[entity.id()], entity);
		archetypes_[entity.id()] -= Archetype::create<T>();
		add_to_group(archetypes_[entity.id()], entity);

		get_array<T>()->remove(entity.id());
	}

	template <typename T>
	T& get_component(const Entity& entity)
	{
		return (*get_array<T>())[entity.id()];
	}

	void add_group(const Archetype& archetype)
	{
		core::check(!groups_.contains(archetype));
		groups_.insert({archetype, {}});
		auto& entities = groups_[archetype];
		for(auto& entity : entities_)
		{
			if(archetypes_[entity.id()] == archetype)
				entities.emplace_back(entity);
		}
	}

	void remove_group(const Archetype& archetype)
	{
		core::check(groups_.contains(archetype));
		groups_.erase(archetype);
	}

	std::vector<Entity>& get_group(const Archetype& archetype)
	{
		core::check(groups_.contains(archetype));
		return groups_[archetype];
	}

private:
	Entity::id_type allocate_id();
	void            deallocate_id(Entity::id_type id);

	void add_to_group(const Archetype& archetype, const Entity& entity)
	{
		auto it = groups_.find(archetype);
		if(it != groups_.end())
			it->second.emplace_back(entity);
	}

	void remove_from_group(const Archetype& archetype, const Entity& entity)
	{
		auto it = groups_.find(archetype);
		if(it != groups_.end())
			it->second.erase(std::ranges::find(it->second, entity));
	}

	template <typename T>
	std::shared_ptr<Array<T>> get_array() const
	{
		return std::static_pointer_cast<Array<T>>(arrays_.at(Typeid<T>()));
	}

	std::vector<Entity>          entities_;
	std::vector<Entity::id_type> freeIds_;
	std::vector<Archetype>       archetypes_;

	std::unordered_map<TypeIndex, std::shared_ptr<ArrayBase>> arrays_;
	std::unordered_map<Archetype, std::vector<Entity>>        groups_;
};

static_assert(std::numeric_limits<Entity::id_type>::max() < std::numeric_limits<size_t>::max());

} // namespace ecs

#include "manager.inl"
