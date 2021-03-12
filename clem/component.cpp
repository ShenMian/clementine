// Copyright 2020 SMS
// License(Apache-2.0)
// ×é¼þ

#include "component.h"

Component::Component()
		: owner(nullptr)
{
}

void Component::update(float)
{
}

void Component::onEnter()
{
}

void Component::onExit()
{
}

void Component::onAdd()
{
}

void Component::onRemove()
{
}

void Component::setOwner(Factor* o)
{
	this->owner = o;
}

Factor* Component::getOwner() const
{
	return owner;
}
