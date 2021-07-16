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
	 * @brief Ĭ�Ϲ��캯��.
	 */
	Entity() = default;

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
	T& add(Args&&... args);

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
	 * @brief ���ʵ���Ƿ���Ч.
	 */
	bool valid() const;

	id_type id() const;

	version_type version() const;

	bool operator==(const Entity& rhs) const;
	bool operator<(const Entity& rhs) const;
	Entity& operator=(const Entity& rhs);

private:
	id_type      id_      = 0;
	version_type version_ = 0;
	Registry*    registry = nullptr;
};

} // namespace clem

#include "Entity.inl"
