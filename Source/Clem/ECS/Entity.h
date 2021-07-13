// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "config.h"
#include <cassert>

namespace clem
{

class Registry;

class Entity
{
public:
	/**
	 * @brief ���캯��.
	 */
	Entity(id_type id, version_type version, Registry& reg);

	/**
	 * @brief ������.
	 * 
	 * @tparam T ���.
	 */
	template <typename T, typename... Args>
	T& emplace(Args&&... args);

	/**
	 * @brief �Ƴ����.
	 * 
	 * @tparam T ���.
	 */
	template <typename T>
	void remove();

	/**
	 * @brief ��ȡ���.
	 * 
	 * @tparam T ���.
	 */
	template <typename T>
	T& get() const;

	/**
	 * @brief �ж��Ƿ���ָ����ȫ�����.
	 * 
	 * @param entity Ҫ����ʵ��.
	 * @tparam Ts ����б�.
	 */
	template <typename... Ts>
	bool allOf() const;

	/**
	 * @brief �ж��Ƿ���ָ�����������.
	 * 
	 * @param entity Ҫ����ʵ��.
	 * @tparam Ts ����б�.
	 */
	template <typename... Ts>
	bool anyOf() const;

	/**
	 * @brief �ж��Ƿ�û��ָ�����κ����.
	 * 
	 * @param entity Ҫ����ʵ��.
	 * @tparam Ts ����б�.
	 */
	template <typename... Ts>
	bool noneOf() const;

	/**
	 * @brief ����Ƿ���Ч.
	 */
	bool valid() const;

	const id_type id;

	const version_type version;

	bool operator==(const Entity& rhs) const;
	bool operator<(const Entity& rhs) const;

private:
	Registry& registry;
};

} // namespace clem

#include "Entity.inl"
