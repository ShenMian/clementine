// Copyright 2021 SMS
// License(Apache-2.0)
// 盒形碰撞体

#ifndef CLEM_PHYSICS_SHAPE_BOX_H_
#define CLEM_PHYSICS_SHAPE_BOX_H_

#include "shape.h"

class Size;
class Point;

/// (已弃用)
class PhysicsShapeBox : public PhysicsShape
{
public:
	PhysicsShapeBox(float x, float y, float width, float height);

	float top() const;
	float bottom() const;
	float left() const;
	float right() const;

	Point tl() const;
	Point tr() const;
	Point bl() const;
	Point br() const;

	Point center() const;

	Size size() const;

private:
	float x, y, width, height;
};

#endif // !CLEM_PHYSICS_SHAPE_BOX_H_

