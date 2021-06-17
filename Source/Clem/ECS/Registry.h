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
	 * @brief ����ʵ��.
	 */
	AEntity create();

	/**
	 * @brief ����ʵ��.
	 */
	void destory(AEntity&);

	/**
	 * @brief ��ȡʵ������.
	 */
	size_t getSize() const;

	/**
	 * @brief ��ȡ Archtype ������.
	 * Archtypes �ɸ������, �Խ�ʡ�ڴ�ռ��.
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
