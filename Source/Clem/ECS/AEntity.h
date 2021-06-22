// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "config.h"
#include <cassert>

namespace clem
{
class Registry;

class AEntity
{
public:
	/**
	 * @brief ���캯��.
	 */
	AEntity(EntityId id, size_t version, Registry& reg);

	/**
	 * @brief ������.
	 */
	template <typename Com, typename... Args>
	Com& add(Args&&... args);

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
	template <typename Com, typename... Coms>
	bool has() const;

	/**
	 * @brief ����Ƿ���Ч.
	 */
	bool isValid() const;

	const EntityId id;

	const size_t version;

	bool operator==(const AEntity& rhs) const;
	bool operator<(const AEntity& rhs) const;

private:
	Registry& registry;
};

} // namespace clem

#include "Entity.inl"
