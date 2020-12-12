// Copyright 2020 SMS
// License(Apache-2.0)
// 物理引擎

#ifndef CLEM_PHYSICS_H_
#define CLEM_PHYSICS_H_

#include <vector>

class Rect;
class Entity;

class Physics
{
public:
	void update(std::vector<Entity*>& entitys) const;
	bool isCollide(const Entity* a, const Entity* b) const;

private:
	bool isCollide(const Rect&, const Rect&) const;
};

#endif // CLEM_PHYSICS_H_
