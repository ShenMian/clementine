// Copyright 2021 SMS
// License(Apache-2.0)

#include "Assert.h"
#include "Registry.h"
#include <cassert>
#include <string>

namespace clem
{

template <typename T, typename... Args>
inline T& Entity::add(Args&&... args)
{
	assert(valid());
	Assert::isTrue(noneOf<T>(), std::format("component already exist: '{}'", typeid(T).name()));
	return registry->addComponent<T>(*this, std::forward<Args>(args)...);
}

template <typename T>
inline void Entity::remove()
{
	assert(valid());
	Assert::isTrue(anyOf<T>(), std::format("component doesn't exist: '{}'", typeid(T).name()));
	registry->removeComponent<T>(*this);
}

template <typename T>
[[nodiscard]] inline T& Entity::get() const
{
	assert(valid());
	Assert::isTrue(anyOf<T>(), std::format("component doesn't exist: '{}'", typeid(T).name()));
	return registry->getComponent<T>(*this);
}

template <typename... Ts>
[[nodiscard]] inline bool Entity::allOf() const
{
	assert(valid());
	return registry->allOf<Ts...>(*this);
}

template <typename... Ts>
[[nodiscard]] inline bool Entity::anyOf() const
{
	assert(valid());
	return registry->anyOf<Ts...>(*this);
}

template <typename... Ts>
[[nodiscard]] inline bool Entity::noneOf() const
{
	assert(valid());
	return registry->noneOf<Ts...>(*this);
}

} // namespace clem