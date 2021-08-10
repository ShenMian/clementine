// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <cfloat>
#include <cmath>
#include <initializer_list>

namespace clem
{

class Vector3;

/**
 * @addtogroup Math
 * @{
 */

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

    Vector3 translation() const;
    Vector3 rotation() const;
    Vector3 scale() const;

    void translate(const Vector3& vec);
    void rotate(float angle, const Vector3& axis);
    void scale(const Vector3& vec);
    void rotateX(float angle);
    void rotateY(float angle);
    void rotateZ(float angle);

    Matrix4& setTranslation(const Vector3& vec);
    Matrix4& setRotation(float angle, const Vector3& axis);
    Matrix4& setScale(const Vector3& vec);
    Matrix4& setRotationX(float angle);
    Matrix4& setRotationY(float angle);
    Matrix4& setRotationZ(float angle);

    Matrix4&     inverse();
    const float* data() const;

    static Matrix4 createPerspective(float fieldOfView, float aspectRatio, float nearPlane, float farPlane);
    static Matrix4 createOrthographic(float zoomX, float zoomY, float nearPlane, float farPlane);
    static Matrix4 createOrthographicOffCenter(float left, float right, float bottom, float top,
                                               float zNearPlane, float zFarPlane);

    Matrix4  operator-() const;
    Matrix4& operator=(const Matrix4&);
    Matrix4  operator+(const Matrix4&) const;
    Matrix4& operator+=(const Matrix4&);
    Matrix4  operator-(const Matrix4&) const;
    Matrix4& operator-=(const Matrix4&);
    Matrix4  operator*(const Matrix4&) const;
    Matrix4& operator*=(const Matrix4&);
    Matrix4  operator*(float) const;
    Matrix4& operator*=(float);

    // Vector4 operator*(const Vector4&) const;

    static const Matrix4 identity;
    static const Matrix4 zero;
};

using Mat4 = Matrix4;

/**
 * end of Math group
 * @}
 */

} // namespace clem