// Copyright 2020 SMS
// License(Apache-2.0)
// 2D矢量

#include "vec2.h"
#include <math.h>

Vec2::Vec2()
		: Vec2(0, 0)
{
}

Vec2::Vec2(float x, float y)
		: x(x), y(y)
{
}

ushort Vec2::distance(const Vec2& vec) const
{
	return Vec2(fabs(x - vec.x), fabs(y - vec.y)).length();
}

ushort Vec2::length() const
{
	return sqrtf(x * x + y * y);
}

bool Vec2::operator==(const Vec2& vec) const
{
	if(x == vec.x && y == vec.y)
		return true;
	else
		return false;
}

bool Vec2::operator!=(const Vec2& vec) const
{
	return !(*this == vec);
}

Vec2 Vec2::operator*(int n) const
{
	return Vec2(x * n, y * n);
}

Vec2 Vec2::operator/(int n) const
{
	return Vec2(x / n, y / n);
}

Vec2 Vec2::operator+(const Vec2& vec) const
{
	return Vec2(x + vec.x, y + vec.y);
}

Vec2 Vec2::operator-(const Vec2& vec) const
{
	return Vec2(x - vec.x, y - vec.y);
}

Vec2& Vec2::operator+=(const Vec2& vec)
{
	x += vec.x;
	y += vec.y;
	return *this;
}

Vec2& Vec2::operator-=(const Vec2& vec)
{
	x -= vec.x;
	y -= vec.y;
	return *this;
}

Vec2& Vec2::operator*=(int n)
{
	x *= n;
	y *= n;
	return *this;
}

Vec2& Vec2::operator/=(int n)
{
	x /= n;
	y /= n;
	return *this;
}
