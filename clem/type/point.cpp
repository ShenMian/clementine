// Copyright 2020 SMS
// License(Apache-2.0)
// зјБъ

#include "point.h"
#include <cmath>
#include "vec2.h"

template <class T>
Point<T>::Point()
		: Point(0, 0)
{
}

template <class T>
Point<T>::Point(T x, T y)
		: x(x), y(y)
{
}

template <class T>
Point<T>::Point(const Vec2& vec)
		: Point(vec.x, vec.y)
{
}

template <class T>
float Point<T>::distance(const Point& p) const
{
	return std::sqrt(std::abs(x - p.x) + std::abs(y - p.y));
}

template <class T>
Point<T> Point<T>::operator+(const Point& p) const
{
	return Point(x + p.x, y + p.y);
}

template <class T>
Point<T> Point<T>::operator-(const Point& p) const
{
	return Point(x - p.x, y - p.y);
}

template <class T>
Point<T> Point<T>::operator+(const Vec2& v) const
{
	return Point(x + v.x, y + v.y);
}

template <class T>
Point<T> Point<T>::operator-(const Vec2& v) const
{
	return Point(x - v.x, y - v.y);
}

template <class T>
const Point<T>& Point<T>::operator+=(const Vec2& v)
{
	x += v.x;
	y += v.y;
	return *this;
}

template <class T>
const Point<T>& Point<T>::operator-=(const Vec2& v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}

