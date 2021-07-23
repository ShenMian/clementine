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
	 * @brief ����ʵ��.
	 */
	Entity create();

	/**
	 * @brief ��������ָ�� Tag �����ʵ��.
	 *
	 * @param tag Tag ������ַ���.
	 */
	Entity create(const std::string& tag);

	/**
	 * @brief ����ʵ��.
	 */
	void destroy(const Entity&);

	/**
	 * @brief ��ȡ����ָ�� Tag �����ʵ��.
	 *
	 * @param tag Tag ������ַ���.
	 */
	Entity get(const std::string& tag);

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
