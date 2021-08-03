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

    void translate(const Vector3& vec);
    void rotate(float angle, Vector3& axis);
    void scale(const Vector3& vec);

    const float* data() const;

    void rotateX(float angle);
    void rotateY(float angle);
    void rotateZ(float angle);

    Vector3 translation() const;
    Vector3 rotation() const;
    Vector3 scale() const;

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

    static const Matrix4 identity;
    static const Matrix4 zero;
};

using Mat4 = Matrix4;

/**
 * end of Math group
 * @}
 */
