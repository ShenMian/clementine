// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Archtype.h"
#include "Chunk.h" // FIXME: incude Entity -> include Registry
#include <functional>
#include <map>
#include <memory_resource>
#include <set>
#include <unordered_map>
#include <unordered_set>

namespace clem
{

class Entity;
class System;

struct EntityInfo
{
	Archtype     archtype;
	version_type version = 0;
	Chunk*       chunk   = nullptr;
};

class Registry
{
public:
	/**
	 * @brief 创建实体.
	 */
	Entity create();

	/**
	 * @brief 创建带有指定 Tag 组件的实体.
	 *
	 * @param tag Tag 组件的字符串.
	 */
	Entity create(const std::string& tag);

	/**
	 * @brief 销毁实体.
	 */
	void destroy(const Entity&);

	/**
	 * @brief 获取带有指定 Tag 组件的实体.
	 *
	 * @param tag Tag 组件的字符串.
	 */
	Entity get(const std::string& tag);

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
	 * @brief 遍历具有指定组件的实体.
	 *
	 * @param func 遍历时将调用的函数, 参数为实体和组件.
	 */
	template <typename Com>
	void each(std::function<void(const Entity&, Com&)> func);

	/**
	 * @brief 更新系统.
	 */
	void update(float dt);

	/**
	 * @brief 添加系统.
	 */
	void addSystem(System*);

	/**
	 * @brief 移除系统.
	 */
	void removeSystem(System*);

	/**
	 * @brief 启用系统.
	 */
	void enableSystem(System*);

	/**
	 * @brief 禁用系统.
	 */
	void disableSystem(System*);

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
	 * @brief 判断是否有指定的全部组件.
	 *
	 * @param entity 要检测的实体.
	 */
	template <typename... Coms>
	bool allOf(const Entity& entity) const;

	/**
	 * @brief 判断是否有指定的任意组件.
	 *
	 * @param entity 要检测的实体.
	 */
	template <typename... Coms>
	bool anyOf(const Entity& entity) const;

	/**
	 * @brief 判断是否没有指定的任何组件.
	 *
	 * @param entity 要检测的实体.
	 */
	template <typename... Coms>
	bool noneOf(const Entity& entity) const;

	/**
	 * @brief 判断实体是否有效.
	 */
	bool valid(const Entity&) const;

private:
	template <typename T>
	using Allocator = std::pmr::polymorphic_allocator<T>;

	std::vector<EntityInfo> entities;
	std::vector<id_type>    freeIds;

	Chunk                      chunk;
	std::map<Archtype, Chunk*> chunks;
	Allocator<Chunk>           allocator;

	std::vector<System*> systems;
	std::vector<System*> disabledSystems;

	id_type requestId();
	void    recycleId(id_type);
};

} // namespace clem

#include "Registry.inl"
