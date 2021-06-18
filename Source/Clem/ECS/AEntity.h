// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "config.h"

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
	Com& addComponent(Args&&... args);

	/**
	 * @brief �Ƴ����.
	 */
	template <typename Com>
	void removeComponent();

	/**
	 * @brief ��ȡ���.
	 */
	template <typename Com>
	Com& getComponent() const;

	/**
	 * @brief ����Ƿ���ָ�����.
	 */
	template <typename Com>
	bool hasComponent() const;

	/**
	 * @brief ����Ƿ���ָ���Ķ�����.
	 */
	template <typename T, typename V, typename... Types>
	bool hasComponent() const;

	bool isValid() const;

	EntityId getId() const;

	size_t getVersion() const;

	bool operator==(const AEntity& rhs) const;
	bool operator<(const AEntity& rhs) const;

private:
	EntityId  id;
	size_t    version;
	Registry& registry;
};

template <typename Com>
bool AEntity::hasComponent() const
{
	return false;
}

template <typename Com, typename T, typename... Types>
bool AEntity::hasComponent() const
{
	return hasComponent<Com>() && hasComponent<T, Types...>();
}
} // namespace clem
