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
 * @brief 4x4 矩阵, 单精度浮点数. 行优先.
 */
class Matrix4
{
public:
    float m[4][4];

    Matrix4(float v = 1.f);
    Matrix4(const Matrix4&);
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

    /**
     * @brief 计算行列式的值.
     */
    float determinant() const;

    /**
     * @brief 求逆.
     */
    Matrix4& inverse();

    /**
     * @brief 获取求逆结果.
     */
    Matrix4 getInversed() const;

    /**
     * @brief 转置.
     */
    void transpose();

    /**
     * @brief 获取转置结果.
     */
    Matrix4 getTransposed() const;

    /**
     * @brief 返回矩阵数据.
     * 行优先矩阵. (有一说一, 比较喜欢列优先矩阵)
     */
    const float* data() const;

    Vector3 up() const;
    Vector3 down() const;
    Vector3 left() const;
    Vector3 right() const;
    Vector3 forword() const;
    Vector3 back() const;

    /**
     * @brief 创建截头锥体观察体, 用于透视投影.
     *
     * @param yFOV        垂直视角范围, 弧度制.
     * @param aspectRatio 宽高比.
     * @param nearPlane   近平面 z 坐标.
     * @param farPlane    远平面 z 坐标.
     */
    static Matrix4 createPerspective(float yFOV, float aspectRatio, float nearPlane, float farPlane);

    /**
     * @brief 以原点为近平面中心创建正投影观观察体, 用于正交投影.
     *
     * @param width     宽度.
     * @param height    高度.
     * @param nearPlane 近平面 z 坐标.
     * @param farPlane  远平面 z 坐标.
     */
    static Matrix4 createOrthographic(float width, float height, float nearPlane, float farPlane);

    /**
     * @brief 创建正投影观观察体, 用于正交投影.
     *
     * @param left      左平面 x 坐标.
     * @param right     右平面 x 坐标.
     * @param bottom    底面 y 坐标.
     * @param top       顶面 y 坐标.
     * @param nearPlane 近平面 z 坐标.
     * @param farPlane  远平面 z 坐标.
     */
    static Matrix4 createOrthographicOffCenter(float left, float right, float bottom, float top,
                                               float nearPlane, float farPlane);

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
    bool     operator==(const Matrix4&) const = default;

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