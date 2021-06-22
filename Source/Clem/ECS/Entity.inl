// Copyright 2021 SMS
// License(Apache-2.0)

namespace clem
{
template <typename Com, typename... Args>
inline Com& Entity::add(Args&&... args)
{
	assert(!has<Com>() && "component already exist");
	return registry.addComponent<Com>(*this, std::forward<Args>(args)...);
}

template <typename Com>
inline void Entity::remove()
{
	assert(has<Com>() && "component doesn't exist");
	registry.removeComponent<Com>(*this);
}

template <typename Com>
[[nodiscard]] inline Com& Entity::get() const
{
	assert(has<Com>() && "component doesn't exist");
	return registry.getComponent<Com>(*this);
}

template <typename Com, typename... Coms>
[[nodiscard]] inline bool Entity::has() const
{
	if constexpr(sizeof...(Coms) > 0)
		return registry.hasComponent<Com>(*this) && registry.hasComponent<Coms...>(*this);
	else
		return registry.hasComponent<Com>(*this);
}
} // namespace clem