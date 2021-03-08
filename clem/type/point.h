// Copyright 2020 SMS
// License(Apache-2.0)
// 坐标

#ifndef CLEM_TYPE_POINT_H_
#define CLEM_TYPE_POINT_H_

class Vec2;

template<class T = float>
class Point
{
public:
	T x;
	T y;

	Point();
	Point(T x, T y);
	Point(const Vec2& vec);

	float distance(const Point<T>&) const;

	Point<T>        operator+(const Point<T>&) const;
	Point<T>        operator-(const Point<T>&) const;
	Point<T>        operator+(const Vec2&) const;
	Point<T>        operator-(const Vec2&) const;
	const Point<T>& operator+=(const Vec2&);
	const Point<T>& operator-=(const Vec2&);
};

#endif // CLEM_TYPE_POINT_H_
