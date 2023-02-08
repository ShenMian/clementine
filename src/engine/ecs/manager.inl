// Copyright 2022 ShenMian
// License(Apache-2.0)

namespace ecs
{

inline Entity Manager::create()
{
	return entities_[allocate_id()];
}

inline void Manager::destroy(const Entity& entity)
{
	if(valid(entity))
		deallocate_id(entity.id());
}

inline bool Manager::valid(const Entity& entity) const noexcept
{
	return entity.id() < entities_.size() && entity == entities_[entity.id()];
}

inline Entity::id_type Manager::allocate_id()
{
	if(freeIds_.empty())
	{
		const auto id = entities_.size();
		entities_.emplace_back(static_cast<Entity::id_type>(id), 0, *this);
		return id;
	}
	const auto id = freeIds_.back();
	freeIds_.pop_back();
	return id;
}

inline void Manager::deallocate_id(Entity::id_type id)
{
	freeIds_.push_back(id);
	entities_[id].version_++;
}

} // namespace ecs
