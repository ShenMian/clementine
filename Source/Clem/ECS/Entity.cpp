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

bool Entity::isValid() const
{
	return registry.isValid(*this);
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