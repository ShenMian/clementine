// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <cfloat>
#include <cmath>
#include <initializer_list>

/**
 * @addtogroup Math
 * @{
 */

class Vector3;

/**
 * @brief 4x4 矩阵, 单精度浮点数.
 */
class Matrix4
{
public:
	float m[4][4];

	Matrix4();
	Matrix4(std::initializer_list<float> list);
	Matrix4(const float* m);

	Vector3 getTranslation() const;
	Vector3 getRotation() const;
	Vector3 getScale() const;

	void translate(const Vector3& vec);
	// void rotate(const Vector3& pivot, float angleX, float angleY, float angleZ);
	void rotateX(float angle);
	void rotateY(float angle);
	void rotateZ(float angle);
	void scale(const Vector3& vec);

	Matrix4  operator-() const;
	Matrix4& operator=(const Matrix4& rhs);
	Matrix4  operator+(const Matrix4& rhs) const;
	Matrix4& operator+=(const Matrix4& rhs);
	Matrix4  operator-(const Matrix4& rhs) const;
	Matrix4& operator-=(const Matrix4& rhs);
	Matrix4  operator*(const Matrix4& rhs) const;
	Matrix4& operator*=(const Matrix4& rhs);
	Matrix4  operator*(float rhs) const;
	Matrix4& operator*=(float rhs);

	static const Matrix4 unit;
	static const Matrix4 zero;
};

using Mat4 = Matrix4;

/**
 * end of Math group
 * @}
 */
