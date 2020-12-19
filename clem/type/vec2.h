// Copyright 2020 SMS
// License(Apache-2.0)
// 2D矢量

#ifndef CLEM_TYPE_VECTOR_H_
#define CLEM_TYPE_VECTOR_H_

#include <math.h>

typedef unsigned short ushort;

class Vec2
{
public:
	float x;
	float y;

	Vec2();
	Vec2(float x, float y);

	ushort distance(const Vec2& vec) const;
	ushort length() const;

	bool    operator==(const Vec2& vec) const;
	bool    operator!=(const Vec2& vec) const;
	Vec2  operator*(int n) const;
	Vec2  operator/(int n) const;
	Vec2  operator+(const Vec2& vec) const;
	Vec2  operator-(const Vec2& vec) const;
	Vec2& operator+=(const Vec2& vec);
	Vec2& operator-=(const Vec2& vec);
	Vec2& operator*=(int n);
	Vec2& operator/=(int n);
};

#endif // CLEM_TYPE_VECTOR_H_
