// Copyright 2020 SMS
// License(Apache-2.0)
// 2D矢量

#ifndef CLEM_TYPE_VECTOR_H_
#define CLEM_TYPE_VECTOR_H_

#include <math.h>

typedef unsigned short ushort;

class Vector
{
public:
	float x;
	float y;

	Vector();
	Vector(float x, float y);

	ushort distance(const Vector& vec) const;
	ushort length() const;

	bool    operator==(const Vector& vec) const;
	bool    operator!=(const Vector& vec) const;
	Vector  operator*(int n) const;
	Vector  operator/(int n) const;
	Vector  operator+(const Vector& vec) const;
	Vector  operator-(const Vector& vec) const;
	Vector& operator+=(const Vector& vec);
	Vector& operator-=(const Vector& vec);
	Vector& operator*=(int n);
	Vector& operator/=(int n);
};

#endif // CLEM_TYPE_VECTOR_H_
