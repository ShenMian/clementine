// Copyright 2021 SMS
// License(Apache-2.0)

#include "Component.h"

namespace clem
{
Entity& Component::getEntity()
{
	return entity;
}

void Component::setEntity(const Entity& e)
{
	entity = e;
}
} // namespace clem