// Copyright 2020 SMS
// License(Apache-2.0)
// 简易物理引擎

#ifndef CLEM_SIMPLE_PHYSICS_H_
#define CLEM_SIMPLE_PHYSICS_H_

#include "physics.h"

#include <vector>

class Entity;
struct Rect;

class SimplePhysics : public Physics
{
public:
	void update(Entity& entity) override;

	void addBorder(const Rect& rect);

private:
	std::vector<Rect> border;
};

#endif // CLEM_SIMPLE_PHYSICS_H_
