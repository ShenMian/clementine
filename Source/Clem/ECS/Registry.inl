// Copyright 2021 SMS
// License(Apache-2.0)

namespace clem
{

template <typename Com>
inline void Registry::each(std::function<void(const Entity&)> func)
{
	for(id_type i = 0; i < entities.size(); i++)
	{
		Entity entity(i, entities[i].version, *this);
		if(entity.isValid() && entity.has<Com>())
			func(entity);
	}
}

template <typename Com, typename... Args>
inline Com& Registry::addComponent(const Entity& e, Args&&... args)
{
	/*auto& chunk = getChunk(e);
	if(chunk.getSize() == chunk.getMaxSize())
	{
		auto newChunk = allocator.allocate(1);
		allocator.deallocate(newChunk, 1);
	}*/
	// entities[id].archtype.add<Com>();
	return getChunk(e).addComponent<Com>(e, std::forward<Args>(args)...);
}

template <typename Com>
inline void Registry::removeComponent(const Entity& e)
{
	getChunk(e).removeComponent<Com>(e);
}

template <typename Com>
[[nodiscard]] inline Com& Registry::getComponent(const Entity& e)
{
	return getChunk(e).getComponent<Com>(e);
}

template <typename Com, typename... Coms>
[[nodiscard]] inline bool Registry::allOf(const Entity& e) const
{
	if constexpr(sizeof...(Coms) > 0)
		return getChunk(e).hasComponent<Com>(e) && getChunk(e).hasComponent<Coms...>(e);
	else
		return getChunk(e).hasComponent<Com>(e);
}
} // namespace clem