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
	template <typename Com, typename... Coms>
	bool hasComponent() const;

	/**
	 * @brief ����Ƿ���Ч.
	 */
	bool isValid() const;

	/**
	 * @brief ��ȡ ID.
	 */
	EntityId getId() const;

	/**
	 * @brief ��ȡ version.
	 */
	size_t getVersion() const;

	bool operator==(const AEntity& rhs) const;
	bool operator<(const AEntity& rhs) const;

private:
	EntityId  id;
	size_t    version;
	Registry& registry;
};

template <typename Com>
inline bool AEntity::hasComponent() const
{
	return false;
}

template <typename Com, typename... Coms>
inline bool AEntity::hasComponent() const
{
	if constexpr(sizeof...(Coms) > 0)
		return hasComponent<Com>() && hasComponent<Coms...>();
	else
		return hasComponent<Com>();
}
} // namespace clem
