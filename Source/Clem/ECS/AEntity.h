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
	template <typename Com, typename... Coms>
	bool hasComponent() const;

	/**
	 * @brief 检查是否有效.
	 */
	bool isValid() const;

	/**
	 * @brief 获取 ID.
	 */
	EntityId getId() const;

	/**
	 * @brief 获取 version.
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
