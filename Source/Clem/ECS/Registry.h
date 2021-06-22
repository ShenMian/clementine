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
	 * @brief ����ʵ��.
	 */
	Entity create();

	/**
	 * @brief ����ʵ��.
	 */
	void destory(const Entity&);

	/**
	 * @brief ��ȡʵ������.
	 */
	size_t getSize() const;

	/**
	 * @brief ������.
	 */
	template <typename Com, typename... Args>
	Com& addComponent(const Entity&, Args&&...);

	/**
	 * @brief �Ƴ����.
	 */
	template <typename Com>
	void removeComponent(const Entity&);

	/**
	 * @brief ��ȡ���.
	 */
	template <typename Com>
	Com& getComponent(const Entity&);

	/**
	 * @brief ����Ƿ���ָ�����.
	 */
	template <typename Com>
	bool hasComponent(const Entity&) const;

	/**
	 * @brief �ж�ʵ���Ƿ���Ч.
	 */
	bool isValid(const Entity&) const;

	/**
	 * @brief ����ϵͳ.
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
