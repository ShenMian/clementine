// Copyright 2021 SMS
// License(Apache-2.0)

#include <string>
#include "Clem/Assert.h"

namespace clem
{

template <typename T, typename... Args>
inline T& Entity::add(Args&&... args)
{
	CLEM_ASSERT_TRUE(noneOf<T>(), std::string("component already exist: ") + typeid(T).name());
	return registry->addComponent<T>(*this, std::forward<Args>(args)...);
}

template <typename T>
inline void Entity::remove()
{
	CLEM_ASSERT_TRUE(anyOf<T>(), std::string("component doesn't exist: ") + typeid(T).name());
	registry->removeComponent<T>(*this);
}

template <typename T>
[[nodiscard]] inline T& Entity::get() const
{
	CLEM_ASSERT_TRUE(anyOf<T>(), std::string("component doesn't exist: ") + typeid(T).name());
	return registry->getComponent<T>(*this);
}

template <typename... Ts>
[[nodiscard]] inline bool Entity::allOf() const
{
	return registry->allOf<Ts...>(*this);
}

template <typename... Ts>
[[nodiscard]] inline bool Entity::anyOf() const
{
	return registry->anyOf<Ts...>(*this);
}

template <typename... Ts>
[[nodiscard]] inline bool Entity::noneOf() const
{
	return registry->noneOf<Ts...>(*this);
}

} // namespace clem