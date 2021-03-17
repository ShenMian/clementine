
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
