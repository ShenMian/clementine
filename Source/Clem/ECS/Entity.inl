// Copyright 2021 SMS
// License(Apache-2.0)

#include "Assert.hpp"
#include "Registry.h"
#include <string>

namespace clem
{

template <typename T, typename... Args>
inline T& Entity::add(Args&&... args)
{
    Assert::isTrue(valid(), "entity is invalid");
    Assert::isTrue(noneOf<T>(), std::format("component already exist: '{}'", typeid(T).name()));
    return registry->addComponent<T>(*this, std::forward<Args>(args)...);
}

template <typename T>
inline void Entity::remove()
{
    Assert::isTrue(valid(), "entity is invalid");
    Assert::isTrue(anyOf<T>(), std::format("component doesn't exist: '{}'", typeid(T).name()));
    registry->removeComponent<T>(*this);
}

template <typename T>
[[nodiscard]] inline T& Entity::get() const
{
    Assert::isTrue(valid(), "entity is invalid");
    Assert::isTrue(anyOf<T>(), std::format("component doesn't exist: '{}'", typeid(T).name()));
    return registry->getComponent<T>(*this);
}

template <typename... Ts>
[[nodiscard]] inline bool Entity::allOf() const
{
    Assert::isTrue(valid(), "entity is invalid");
    return registry->allOf<Ts...>(*this);
}

template <typename... Ts>
[[nodiscard]] inline bool Entity::anyOf() const
{
    Assert::isTrue(valid(), "entity is invalid");
    return registry->anyOf<Ts...>(*this);
}

template <typename... Ts>
[[nodiscard]] inline bool Entity::noneOf() const
{
    Assert::isTrue(valid(), "entity is invalid");
    return registry->noneOf<Ts...>(*this);
}

} // namespace clem