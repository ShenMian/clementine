// Copyright 2021 SMS
// License(Apache-2.0)

#include "Entity.h"
#include "Registry.h"

namespace clem
{

Entity::Entity(id_type id, version_type ver, Registry& reg)
		: id(id), version(ver), registry(reg)
{
}

[[nodiscard]] bool Entity::valid() const
{
	return registry.valid(*this);
}

bool Entity::operator==(const Entity& rhs) const
{
	return id == rhs.id && &registry == &rhs.registry;
}

bool Entity::operator<(const Entity& rhs) const
{
	return id < rhs.id;
}

} // namespace clem