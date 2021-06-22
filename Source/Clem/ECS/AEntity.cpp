// Copyright 2021 SMS
// License(Apache-2.0)

#include "AEntity.h"
#include "Registry.h"

namespace clem
{
AEntity::AEntity(EntityId id, size_t ver, Registry& reg)
		: id(id), version(ver), registry(reg)
{
}

bool AEntity::operator==(const AEntity& rhs) const
{
	return id == rhs.id && &registry == &rhs.registry;
}

bool AEntity::operator<(const AEntity& rhs) const
{
	return id < rhs.id;
}
} // namespace clem