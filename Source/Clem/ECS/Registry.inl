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
		if(valid(entity) && allOf<Com>(entity))
			func(entity);
	}
}

template <typename Com>
inline void Registry::each(std::function<void(const Entity&, Com&)> func)
{
	each<Com>([&](const Entity& entity) {
		func(entity, getComponent<Com>(entity));
	});
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

	entities[e.id()].archtype.add<Com>();
	return getChunk(e).addComponent<Com>(e, std::forward<Args>(args)...);
}

template <typename Com>
inline void Registry::removeComponent(const Entity& e)
{
	entities[e.id()].archtype.remove<Com>();
	getChunk(e).removeComponent<Com>(e);
}

template <typename Com>
[[nodiscard]] inline Com& Registry::getComponent(const Entity& e)
{
	return getChunk(e).getComponent<Com>(e);
}

template <typename... Coms>
[[nodiscard]] inline bool Registry::allOf(const Entity& e) const
{
	return entities[e.id()].archtype.all<Coms...>();
}

template <typename... Coms>
[[nodiscard]] inline bool Registry::anyOf(const Entity& e) const
{
	return entities[e.id()].archtype.any<Coms...>();
}

template <typename... Coms>
[[nodiscard]] inline bool Registry::noneOf(const Entity& e) const
{
	return entities[e.id()].archtype.none<Coms...>();
}

} // namespace clem