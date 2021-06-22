// Copyright 2021 SMS
// License(Apache-2.0)

#include "Entity.h"
#include "Clem/Components/Tag.h"
#include "Scene.h"

namespace clem
{
OldEntity::OldEntity(id_t id, Scene* scene)
		: id(id), scene(scene)
{
}

OldEntity::id_t OldEntity::getId() const
{
	return id;
}

Scene* OldEntity::getScene() const
{
	return scene;
}

OldEntity::operator bool() const
{
	return id != entt::null;
}

OldEntity::operator id_t() const
{
	return id;
}

bool OldEntity::operator==(const OldEntity& o) const
{
	return id == o.getId();
}

bool OldEntity::operator!=(const OldEntity& o) const
{
	return !(*this == o);
}

void OldEntity::onAddComponent(Component* com)
{
}
} // namespace clem