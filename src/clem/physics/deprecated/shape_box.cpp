// Copyright 2021 SMS
// License(Apache-2.0)
// ������ײ��

#include "shape_box.h"
#include "clem/type.h"

PhysicsShapeBox::PhysicsShapeBox(float x, float y, float w, float h)
		: x(x), y(y), width(w), height(h)
{
}

float PhysicsShapeBox::top() const
{
	return y;
}

float PhysicsShapeBox::bottom() const
{
	return y - height;
}

float PhysicsShapeBox::left() const
{
	return x;
}

float PhysicsShapeBox::right() const
{
	return x + width;
}

Point PhysicsShapeBox::tl() const
{
	return Point(left(), top());
}

Point PhysicsShapeBox::tr() const
{
	return Point(right(), top());
}

Point PhysicsShapeBox::bl() const
{
	return Point(left(), bottom());
}

Point PhysicsShapeBox::br() const
{
	return Point(right(), bottom());
}

Point PhysicsShapeBox::center() const
{
	return Point(x + width / 2, y - height / 2);
}

Size PhysicsShapeBox::size() const
{
	return Size(width, height);
}

