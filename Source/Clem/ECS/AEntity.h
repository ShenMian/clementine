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
	 * @brief 构造函数.
	 */
	AEntity(EntityId id, size_t version, Registry& reg);

	/**
	 * @brief 添加组件.
	 */
	template <typename Com, typename... Args>
	Com& addComponent(Args&&... args);

	/**
	 * @brief 移除组件.
	 */
	template <typename Com>
	void removeComponent();

	/**
	 * @brief 获取组件.
	 */
	template <typename Com>
	Com& getComponent() const;

	/**
	 * @brief 检查是否有指定组件.
	 */
	template <typename Com>
	bool hasComponent() const;

	/**
	 * @brief 检查是否有指定的多个组件.
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
