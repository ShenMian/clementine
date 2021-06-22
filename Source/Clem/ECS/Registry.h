// Copyright 2021 SMS
// License(Apache-2.0)

#include "Archtype.h"
#include "Chunk.h"
#include "Entity.h"
#include "config.h"
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
	 * @brief 销毁实体.
	 */
	void destory(const Entity&);

	/**
	 * @brief 获取实体数量.
	 */
	size_t getSize() const;

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
	 * @brief 检查是否有指定组件.
	 */
	template <typename Com>
	bool hasComponent(const Entity&) const;

	/**
	 * @brief 判断实体是否有效.
	 */
	bool isValid(const Entity&) const;

	/**
	 * @brief 更新系统.
	 */
	void update(float dt);

private:
	template <typename T>
	using Allocator = std::pmr::polymorphic_allocator<T>;

	std::vector<EntityInfo>    entities;
	std::vector<id_type>       freeId;
	std::vector<System*>       systems;
	std::map<Archtype, Chunk*> chunks; // std::unordered_map
	Allocator<Chunk>           allocator;

	Chunk chunk;

	id_type getNewId();
	Chunk&  getChunk(const Entity&) const;
};
} // namespace clem

#include "Registry.inl"
