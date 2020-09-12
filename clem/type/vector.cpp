// Copyright 2020 SMS
// License(Apache-2.0)
// 2D矢量

#include "vector.h"
#include <math.h>

Vector::Vector()
		: Vector(0, 0)
{
}

Vector::Vector(float x, float y)
		: x(x), y(y)
{
}

ushort Vector::distance(const Vector& vec) const
{
	return Vector(fabs(x - vec.x), fabs(y - vec.y)).length();
}

ushort Vector::length() const
{
	return sqrtf(x * x + y * y);
}

bool Vector::operator==(const Vector& vec) const
{
	if(x == vec.x && y == vec.y)
		return true;
	else
		return false;
}

bool Vector::operator!=(const Vector& vec) const
{
	return !(*this == vec);
}

Vector Vector::operator*(int n) const
{
	return Vector(x * n, y * n);
}

Vector Vector::operator/(int n) const
{
	return Vector(x / n, y / n);
}

Vector Vector::operator+(const Vector& vec) const
{
	return Vector(x + vec.x, y + vec.y);
}

Vector Vector::operator-(const Vector& vec) const
{
	return Vector(x - vec.x, y - vec.y);
}

Vector& Vector::operator+=(const Vector& vec)
{
	x += vec.x;
	y += vec.y;
	return *this;
}

Vector& Vector::operator-=(const Vector& vec)
{
	x -= vec.x;
	y -= vec.y;
	return *this;
}

Vector& Vector::operator*=(int n)
{
	x *= n;
	y *= n;
	return *this;
}

Vector& Vector::operator/=(int n)
{
	x /= n;
	y /= n;
	return *this;
}
