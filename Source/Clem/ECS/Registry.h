// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Archtype.h"
#include "Chunk.h"
#include "Entity.h"
#include "config.h"
#include <functional>
#include <memory_resource>
#include <set>
#include <unordered_map>
#include <unordered_set>

namespace clem
{

class System;

struct EntityInfo
{
	Archtype     archtype;
	Chunk*       chunk   = nullptr;
	version_type version = 0;
};

class Registry
{
public:
	/**
	 * @brief 创建实体.
	 */
	Entity create();

	/**
	 * @brief 销毁实体.
	 */
	void destroy(const Entity&);

	/**
	 * @brief 获取实体数量.
	 */
	size_t getSize() const;

	/**
	 * @brief 遍历具有指定组件的实体.
	 * 
	 * @param func 遍历时将调用的函数, 参数为实体.
	 */
	template <typename Com>
	void each(std::function<void(const Entity&)> func);

	/**
	 * @brief 添加组件.
	 */
	template <typename Com, typename... Args>
	Com& addComponent(const Entity&, Args&&...);

	/**
	 * @brief 移除组件.
	 */
	template <typename Com>
	void removeComponent(const Entity&);

	/**
	 * @brief 获取组件.
	 */
	template <typename Com>
	Com& getComponent(const Entity&);

	/**
	 * @brief 检查是否包含全部指定组件.
	 * 
	 * @param entity 要检测的实体.
	 */
	template <typename Com, typename... Coms>
	bool allOf(const Entity& entity) const;

	/**
	 * @brief 检查是否存在指定组件.
	 * 
	 * @param entity 要检测的实体.
	 */
	template <typename Com, typename... Coms>
	bool anyOf(const Entity&) const;

	/**
	 * @brief 判断实体是否有效.
	 */
	bool isValid(const Entity&) const;

	/**
	 * @brief 更新系统.
	 */
	void update(float dt);

	/**
	 * @brief 添加系统.
	 */
	void addSystem(System&);

	/**
	 * @brief 移除系统.
	 */
	void removeSystem(System&);

	/**
	 * @brief 启用系统.
	 */
	void enableSystem(System&);

	/**
	 * @brief 禁用系统.
	 */
	void disableSystem(System&);

private:
	template <typename T>
	using Allocator = std::pmr::polymorphic_allocator<T>;

	std::vector<EntityInfo> entities;
	std::vector<id_type>    freeIds;

	std::vector<System*> systems;
	std::vector<System*> disabledSystems;

	std::map<Archtype, Chunk*> chunks; // std::unordered_map
	Allocator<Chunk>           allocator;

	Chunk chunk;

	id_type getNewId();
	Chunk&  getChunk(const Entity&) const;
};

} // namespace clem

#include "Registry.inl"
