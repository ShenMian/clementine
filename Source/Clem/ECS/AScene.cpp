// Copyright 2021 SMS
// License(Apache-2.0)

#include "AScene.h"
#include "AEntity.h"
#include "Archtype.h"
#include <algorithm>

namespace clem
{
AEntity AScene::createEntity()
{
	// AEntity entity(entities.size(), *this);
	// entities.emplace(entity);
	// return entity;
	return AEntity(0, *this);
}

void AScene::destoryEntity(AEntity entity)
{
	// entities.erase(entities.find(entity));
}

void AScene::view(const Archtype& archtype)
{
	auto it = std::find(archtypes.begin(), archtypes.end(), archtype);
}

class Iterator
{
	Iterator& operator++();
	Iterator& operator++(int);
};
} // namespace clem