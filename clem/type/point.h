// Copyright 2020 SMS
// License(Apache-2.0)
// 坐标

#ifndef CLEM_TYPE_COORD_H_
#define CLEM_TYPE_COORD_H_

class Vector;

typedef unsigned short ushort;

class Point
{
public:
	float x;
	float y;

	Point();
	Point(float x, float y);
	Point(const Vector& vec);

	Point operator+(const Point& pos) const;
	Point operator-(const Point& pos) const;
	Point operator+(const Vector& vec) const;
	Point operator-(const Vector& vec) const;
};

#endif // CLEM_TYPE_COORD_H_
