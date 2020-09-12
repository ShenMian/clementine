// Copyright 2020 SMS
// License(Apache-2.0)
// ŒÔ¿Ì“˝«Ê

#ifndef CLEM_PHYSICS_H_
#define CLEM_PHYSICS_H_

#include "entity.h"

class Physics
{
public:
	virtual void update(Entity&) = 0;
};

#endif // CLEM_PHYSICS_H_
