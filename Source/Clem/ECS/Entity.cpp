// Copyright 2021 SMS
// License(Apache-2.0)

#include "Entity.h"
#include "Registry.h"

namespace clem
{

Entity::Entity(id_type id, version_type ver, Registry& reg)
    : id_(id), version_(ver), registry(&reg)
{
}

Entity::Entity(id_type id, Registry& reg)
    : id_(id), registry(&reg), version_(reg.getVersion(id_))
{
}

[[nodiscard]] bool Entity::valid() const
{
    if(registry)
        return registry->valid(*this);
    return false;
}

id_type Entity::id() const
{
    return id_;
}

version_type Entity::version() const
{
    return version_;
}

bool Entity::operator==(const Entity& rhs) const
{
    return id_ == rhs.id_ && &registry == &rhs.registry;
}

bool Entity::operator<(const Entity& rhs) const
{
    return id_ < rhs.id_;
}

Entity& Entity::operator=(const Entity& rhs)
{
    id_      = rhs.id_;
    version_ = rhs.version_;
    registry = rhs.registry;
    return *this;
}

} // namespace clem