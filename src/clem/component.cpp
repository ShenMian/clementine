// Copyright 2021 SMS
// License(Apache-2.0)

#include "Component.h"

void Component::onAdd()
{
}

void Component::onRemove()
{
}

void Component::setScene(Scene* s)
{
	scene = s;
}

Scene* Component::getScene() const
{
	return scene;
}
