// Copyright 2021 SMS
// License(Apache-2.0)

#include "AEntity.h"
#include "Archtype.h"
#include "Chunk.h"
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
	Archtype archtype;
	Chunk*   chunk   = nullptr;
	size_t   version = 0;
};

class Registry
{
public:
	/**
	 * @brief 创建实体.
	 */
	AEntity create();

	/**
	 * @brief 销毁实体.
	 */
	void destory(const AEntity&);

	/**
	 * @brief 获取实体数量.
	 */
	size_t getSize() const;

	/**
	 * @brief 添加组件.
	 */
	template <typename Com, typename... Args>
	Com& addComponent(const AEntity&, Args&&...);

	/**
	 * @brief 移除组件.
	 */
	template <typename Com>
	void removeComponent(const AEntity&);

	/**
	 * @brief 获取组件.
	 */
	template <typename Com>
	Com& getComponent(const AEntity&);

	/**
	 * @brief 检查是否有指定组件.
	 */
	template <typename Com>
	bool hasComponent(const AEntity&) const;

	/**
	 * @brief 判断实体是否有效.
	 */
	bool isValid(const AEntity&) const;

	/**
	 * @brief 更新系统.
	 */
	void update(float dt);

private:
	template <typename T>
	using Allocator = std::pmr::polymorphic_allocator<T>;

	std::vector<EntityInfo>    entities;
	std::vector<EntityId>      freeId;
	std::vector<System*>       systems;
	std::map<Archtype, Chunk*> chunks; // std::unordered_map
	Allocator<Chunk>           allocator;

	Chunk chunk;

	EntityId getNewId();
	Chunk&   getChunk(const AEntity&) const;
};

template <typename Com, typename... Args>
inline Com& Registry::addComponent(const AEntity& e, Args&&... args)
{
	/*auto& chunk = getChunk(e);
	if(chunk.getSize() == chunk.getMaxSize())
	{
		auto newChunk = allocator.allocate(1);
		allocator.deallocate(newChunk, 1);
	}*/
	// entities[id].archtype.add<Com>();
	return getChunk(e).addComponent<Com>(e, std::forward<Args>(args)...);
}

template <typename Com>
inline void Registry::removeComponent(const AEntity& e)
{
	getChunk(e).removeComponent<Com>(e);
}

template <typename Com>
[[nodiscard]] inline Com& Registry::getComponent(const AEntity& e)
{
	return getChunk(e).getComponent<Com>(e);
}

template <typename Com>
[[nodiscard]] inline bool Registry::hasComponent(const AEntity& e) const
{
	return getChunk(e).hasComponent<Com>(e);
}

} // namespace clem
