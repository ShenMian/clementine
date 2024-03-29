// Copyright 2023 ShenMian
// License(Apache-2.0)

#pragma once

#include "archetype.hpp"
#include "component.hpp"
#include "core/check.hpp"
#include "entity.hpp"
#include "packed_array.hpp"
#include <concepts>
#include <memory>
#include <numeric>
#include <tuple>
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
	Entity create() { return entities_[allocate_id()]; }

	/**
	 * @brief 销毁实体.
	 *
	 * @param entity 要销毁的实体.
	 */
	void destroy(const Entity& entity)
	{
		if(valid(entity))
			deallocate_id(entity.id());
	}

	/**
	 * @brief 判断实体是否有效.
	 *
	 * 被销毁的实体会失效.
	 */
	bool valid(const Entity& entity) const noexcept
	{
		return entity.id() < entities_.size() && entity == entities_[entity.id()];
	}

	/**
	 * @brief 向实体添加组件.
	 *
	 * @param entity 要添加组件的实体.
	 */
	template <std::derived_from<Component> T>
	T& add_component(const Entity& entity)
	{
		if(!component_arrays_.contains(Typeid<T>()))
			component_arrays_.insert({Typeid<T>(), std::make_shared<PackedArray<T>>()});

		remove_from_group(archetypes_[entity.id()], entity);
		archetypes_[entity.id()] += Archetype::create<T>();
		add_to_group(archetypes_[entity.id()], entity);

		return get_component_array<T>()->insert(entity.id());
	}

	template <std::derived_from<Component>... Ts>
	std::tuple<Ts&...> add_components(const Entity& entity)
	{
		return {add_component<Ts>(entity)...};
	}

	/**
	 * @brief 从实体移除组件.
	 *
	 * @param entity 要移除组件的实体.
	 */
	template <std::derived_from<Component> T>
	void remove_component(const Entity& entity)
	{
		remove_from_group(archetypes_[entity.id()], entity);
		archetypes_[entity.id()] -= Archetype::create<T>();
		add_to_group(archetypes_[entity.id()], entity);

		get_component_array<T>()->remove(entity.id());
	}

	/**
	 * @brief 从实体获取组件.
	 *
	 * @param entity 要获取组件的实体.
	 */
	template <std::derived_from<Component> T>
	T& get_component(const Entity& entity)
	{
		return (*get_component_array<T>())[entity.id()];
	}

	template <std::derived_from<Component> T>
	const T& get_component(const Entity& entity) const
	{
		return (*get_component_array<T>())[entity.id()];
	}

	template <std::derived_from<Component>... Ts>
	std::tuple<Ts&...> get_components(const Entity& entity)
	{
		return {get_component<Ts>(entity)...};
	}

	void add_group(const Archetype& archetype)
	{
		CLEM_DEBUG_CHECK(!groups_.contains(archetype));
		groups_.insert({archetype, {}});
		auto& entities = groups_[archetype];
		for(auto& entity : entities_)
		{
			if(archetypes_[entity.id()] == archetype)
				entities.emplace_back(entity);
		}
	}

	template <std::derived_from<Component>... Ts>
	void add_group()
	{
		add_group(Archetype::create<Ts...>());
	}

	void remove_group(const Archetype& archetype)
	{
		CLEM_DEBUG_CHECK(groups_.contains(archetype));
		groups_.erase(archetype);
	}

	template <std::derived_from<Component>... Ts>
	void remove_group()
	{
		remove_group(Archetype::create<Ts...>());
	}

	std::vector<Entity>& get_group(const Archetype& archetype)
	{
		CLEM_DEBUG_CHECK(groups_.contains(archetype));
		return groups_[archetype];
	}

	template <std::derived_from<Component>... Ts>
	std::vector<Entity>& get_group()
	{
		return get_group(Archetype::create<Ts...>());
	}

	// template <typename... Ts>
	// View<Ts...> get_group()
	// {
	// 	const auto archetype = Archetype::create<Ts...>();
	// 	CLEM_DEBUG_CHECK(groups_.contains(archetype));
	// 	return {groups_[archetype], *this};
	// }

private:
	Entity::id_type allocate_id()
	{
		if(freeIds_.empty())
		{
			const auto id = entities_.size();
			entities_.emplace_back(static_cast<Entity::id_type>(id), 0);
			archetypes_.emplace_back();
			return id;
		}
		const auto id = freeIds_.back();
		freeIds_.pop_back();
		return id;
	}

	void deallocate_id(Entity::id_type id)
	{
		freeIds_.push_back(id);
		entities_[id].version_++;
	}

	void add_to_group(const Archetype& archetype, const Entity& entity)
	{
		auto it = groups_.find(archetype);
		if(it != groups_.end())
			it->second.emplace_back(entity);
	}

	void remove_from_group(const Archetype& archetype, const Entity& entity)
	{
		const auto it = groups_.find(archetype);
		if(it != groups_.end())
			it->second.erase(std::ranges::find(it->second, entity));
	}

	template <typename T>
	std::shared_ptr<PackedArray<T>> get_component_array()
	{
		return std::static_pointer_cast<PackedArray<T>>(component_arrays_.at(Typeid<T>()));
	}

	std::vector<Entity>                                             entities_;
	std::vector<Archetype>                                          archetypes_;
	std::unordered_map<TypeIndex, std::shared_ptr<PackedArrayBase>> component_arrays_;

	std::unordered_map<Archetype, std::vector<Entity>> groups_;

	std::vector<Entity::id_type> freeIds_;
};

} // namespace ecs
