// Copyright 2020 SMS
// License(Apache-2.0)
// 坐标

#ifndef CLEM_TYPE_COORD_H_
#define CLEM_TYPE_COORD_H_

class Vec2;

typedef unsigned short ushort;

class Point
{
public:
	float x;
	float y;

	Point();
	Point(float x, float y);
	Point(const Vec2& vec);

	Point operator+(const Point&) const;
	Point operator-(const Point&) const;
	Point operator+(const Vec2&) const;
	Point operator-(const Vec2&) const;
	const Point& operator+=(const Vec2&);
	const Point& operator-=(const Vec2&);
};

#endif // CLEM_TYPE_COORD_H_
