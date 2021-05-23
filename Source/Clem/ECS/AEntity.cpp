// Copyright 2021 SMS
// License(Apache-2.0)

#include "AEntity.h"
#include "AScene.h"

namespace clem
{

AEntity::AEntity(size_t id, AScene& scene)
		: id(id), scene(scene)
{
}

bool AEntity::operator==(const AEntity& rhs) const
{
	return id == rhs.id && &scene == &rhs.scene;
}

bool AEntity::operator<(const AEntity& rhs) const
{
	return id < rhs.id;
}

} // namespace clem
