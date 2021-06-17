// Copyright 2021 SMS
// License(Apache-2.0)

#include "AEntity.h"
#include "config.h"
#include <memory_resource>
#include <set>
#include <unordered_map>

namespace clem
{

class Archtype;
class Chunk;
struct EntityInfo;

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
	void destory(AEntity&);

	/**
	 * @brief 获取实体数量.
	 */
	size_t getSize() const;

	/**
	 * @brief 获取 Archtype 的引用.
	 * Archtypes 由该类管理, 以节省内存占用.
	 */
	const Archtype& getArchtype(const Archtype&);

private:
	std::vector<EntityInfo>                entities;
	std::vector<EntityId>                  freeId;
	std::set<Archtype>                     archtypes; // std::unordered_set
	std::unordered_map<Archtype*, Chunk*>  chunks;
	std::pmr::polymorphic_allocator<Chunk> allocator;

	EntityId getNewId();
};

} // namespace clem
