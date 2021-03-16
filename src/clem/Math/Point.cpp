// Copyright 2021 SMS
// License(Apache-2.0)

#include "Point.h"
#include "Vec2.h"
#include <cmath>
#include <algorithm>

Point::Point()
		: x(0), y(0)
{
}

Point::Point(float x, float y)
		: x(x), y(y)
{
}

float Point::distance(const Point& o) const
{
	return std::sqrt(distanceSquared(o));
}

float Point::distanceSquared(const Point& o) const
{
	auto xDis = std::abs(x - o.x);
	auto yDis = std::abs(y - o.y);
	return xDis * xDis + yDis * yDis;
}

void Point::clamp(Point min, Point max)
{
	x = std::max(x, min.x);
	x = std::min(x, max.x);
	y = std::max(y, min.y);
	y = std::min(y, max.y);
}

Point Point::getMidpoint(const Point& other) const
{
	return Point((x + other.x) / 2.0f, (y + other.y) / 2.0f);
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

Point& Point::operator+=(const Vec2& v)
{
	x += v.x;
	y += v.y;
	return *this;
}

Point& Point::operator-=(const Vec2& v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}
