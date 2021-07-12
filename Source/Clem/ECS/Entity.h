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
	 */
	template <typename Com, typename... Args>
	Com& emplace(Args&&... args);

	/**
	 * @brief �Ƴ����.
	 */
	template <typename Com>
	void remove();

	/**
	 * @brief ��ȡ���.
	 */
	template <typename Com>
	Com& get() const;

	/**
	 * @brief ����Ƿ���ָ���Ķ�����.
	 */
	template <typename... Coms>
	bool has() const;

	/**
	 * @brief ����Ƿ���Ч.
	 */
	bool isValid() const;

	const id_type id;

	const version_type version;

	bool operator==(const Entity& rhs) const;
	bool operator<(const Entity& rhs) const;

private:
	Registry& registry;
};

} // namespace clem

#include "Entity.inl"
