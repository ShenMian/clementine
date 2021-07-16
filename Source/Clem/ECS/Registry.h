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
	 * @brief ����ʵ��.
	 */
	Entity create();

	Entity create(const std::string&);

	/**
	 * @brief ����ʵ��.
	 */
	void destroy(const Entity&);

	Entity get(const std::string&);

	/**
	 * @brief ��ȡʵ������.
	 */
	size_t getSize() const;

	/**
	 * @brief ��������ָ�������ʵ��.
	 * 
	 * @param func ����ʱ�����õĺ���, ����Ϊʵ��.
	 */
	template <typename Com>
	void each(std::function<void(const Entity&)> func);

	/**
	 * @brief ��������ָ�������ʵ��.
	 * 
	 * @param func ����ʱ�����õĺ���, ����Ϊʵ������.
	 */
	template <typename Com>
	void each(std::function<void(const Entity&, Com&)> func);

	/**
	 * @brief ����ϵͳ.
	 */
	void update(float dt);

	/**
	 * @brief ���ϵͳ.
	 */
	void addSystem(System*);

	/**
	 * @brief �Ƴ�ϵͳ.
	 */
	void removeSystem(System*);

	/**
	 * @brief ����ϵͳ.
	 */
	void enableSystem(System*);

	/**
	 * @brief ����ϵͳ.
	 */
	void disableSystem(System*);


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
	 * @brief �ж��Ƿ���ָ����ȫ�����.
	 * 
	 * @param entity Ҫ����ʵ��.
	 */
	template <typename... Coms>
	bool allOf(const Entity& entity) const;

	/**
	 * @brief �ж��Ƿ���ָ�����������.
	 * 
	 * @param entity Ҫ����ʵ��.
	 */
	template <typename... Coms>
	bool anyOf(const Entity& entity) const;

	/**
	 * @brief �ж��Ƿ�û��ָ�����κ����.
	 * 
	 * @param entity Ҫ����ʵ��.
	 */
	template <typename... Coms>
	bool noneOf(const Entity& entity) const;

	/**
	 * @brief �ж�ʵ���Ƿ���Ч.
	 */
	bool valid(const Entity&) const;

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

	id_type requestId();
	void    recycleId(id_type);

	Chunk&  getChunk(const Entity&) const;
};

} // namespace clem

#include "Registry.inl"
