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
	 * @brief 构造函数.
	 */
	AEntity(EntityId id, size_t version, Registry& reg);

	/**
	 * @brief 添加组件.
	 */
	template <typename Com, typename... Args>
	Com& add(Args&&... args);

	/**
	 * @brief 移除组件.
	 */
	template <typename Com>
	void remove();

	/**
	 * @brief 获取组件.
	 */
	template <typename Com>
	Com& get() const;

	/**
	 * @brief 检查是否有指定的多个组件.
	 */
	template <typename Com, typename... Coms>
	bool has() const;

	/**
	 * @brief 检查是否有效.
	 */
	bool isValid() const;

	const EntityId id;

	const size_t version;

	bool operator==(const AEntity& rhs) const;
	bool operator<(const AEntity& rhs) const;

private:
	Registry& registry;
};

template <typename Com, typename... Args>
inline Com& AEntity::add(Args&&... args)
{
	assert(!has<Com>() && "component already exist");
	return registry.addComponent<Com>(*this, std::forward<Args>(args)...);
}

template <typename Com>
inline void AEntity::remove()
{
	assert(has<Com>() && "component doesn't exist");
	registry.removeComponent<Com>(*this);
}

template <typename Com>
[[nodiscard]] inline Com& AEntity::get() const
{
	assert(has<Com>() && "component doesn't exist");
	return registry.getComponent<Com>(*this);
}

template <typename Com, typename... Coms>
[[nodiscard]] inline bool AEntity::has() const
{
	if constexpr(sizeof...(Coms) > 0)
		return registry.hasComponent<Com>(*this) && registry.hasComponent<Coms...>(*this);
	else
		return registry.hasComponent<Com>(*this);
}

} // namespace clem
