// Copyright 2020 SMS
// License(Apache-2.0)
// зјБъ

#include "point.h"
#include "vector.h"

Point::Point()
		: Point(0, 0)
{
}

Point::Point(float x, float y)
		: x(x), y(y)
{
}

Point::Point(const Vector& vec)
		: Point(vec.x, vec.y)
{
}

Point Point::operator+(const Vector& vec) const
{
	return Point(x + vec.x, y + vec.y);
}

Point Point::operator-(const Vector& vec) const
{
	return Point(x - vec.x, y - vec.y);
}
