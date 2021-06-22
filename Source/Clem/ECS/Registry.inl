// Copyright 2021 SMS
// License(Apache-2.0)

namespace clem
{
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

template <typename Com>
[[nodiscard]] inline bool Registry::hasComponent(const Entity& e) const
{
	return getChunk(e).hasComponent<Com>(e);
}
} // namespace clem