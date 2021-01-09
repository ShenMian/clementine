// Copyright 2020 SMS
// License(Apache-2.0)
// зјБъ

#include "point.h"
#include <cmath>
#include "vec2.h"

Point::Point()
		: Point(0, 0)
{
}

Point::Point(float x, float y)
		: x(x), y(y)
{
}

Point::Point(const Vec2& vec)
		: Point(vec.x, vec.y)
{
}

float Point::distance(const Point& p) const
{
	return std::sqrt(std::abs(x - p.x) + std::abs(y - p.y));
}

Point Point::operator+(const Point& p) const
{
	return Point(x + p.x, y + p.y);
}

Point Point::operator-(const Point& p) const
{
	return Point(x - p.x, y - p.y);
}

Point Point::operator+(const Vec2& v) const
{
	return Point(x + v.x, y + v.y);
}

Point Point::operator-(const Vec2& v) const
{
	return Point(x - v.x, y - v.y);
}

const Point& Point::operator+=(const Vec2& v)
{
	x += v.x;
	y += v.y;
	return *this;
}

const Point& Point::operator-=(const Vec2& v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}
