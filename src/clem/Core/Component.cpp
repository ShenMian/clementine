// Copyright 2021 SMS
// License(Apache-2.0)

#include "Component.h"

void NComponent::onAdd()
{
}

void NComponent::onRemove()
{
}

void NComponent::setScene(NScene* s)
{
	scene = s;
}

NScene* NComponent::getScene() const
{
	return scene;
}
