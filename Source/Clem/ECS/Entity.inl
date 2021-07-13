// Copyright 2021 SMS
// License(Apache-2.0)

namespace clem
{

template <typename T, typename... Args>
inline T& Entity::emplace(Args&&... args)
{
	assert(!anyOf<T>() && "component already exist");
	return registry.addComponent<T>(*this, std::forward<Args>(args)...);
}

template <typename T>
inline void Entity::remove()
{
	assert(anyOf<T>() && "component doesn't exist");
	registry.removeComponent<T>(*this);
}

template <typename T>
[[nodiscard]] inline T& Entity::get() const
{
	assert(anyOf<T>() && "component doesn't exist");
	return registry.getComponent<T>(*this);
}

template <typename... Ts>
[[nodiscard]] inline bool Entity::allOf() const
{
	return registry.allOf<Ts...>(*this);
}

template <typename... Ts>
[[nodiscard]] inline bool Entity::anyOf() const
{
	return registry.anyOf<Ts...>(*this);
}

template <typename... Ts>
[[nodiscard]] inline bool Entity::noneOf() const
{
	return registry.noneOf<Ts...>(*this);
}

} // namespace clem