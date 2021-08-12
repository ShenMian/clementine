// Copyright 2021 SMS
// License(Apache-2.0)

#include "Matrix4.h"
#include "Assert.hpp"
#include "Vector3.h"
#include <cmath>
#include <cstring>

namespace clem
{

const Matrix4 Matrix4::identity = {
    1.f, 0.f, 0.f, 0.f,
    0.f, 1.f, 0.f, 0.f,
    0.f, 0.f, 1.f, 0.f,
    0.f, 0.f, 0.f, 1.f};

const Matrix4 Matrix4::zero = {
    0.f, 0.f, 0.f, 0.f,
    0.f, 0.f, 0.f, 0.f,
    0.f, 0.f, 0.f, 0.f,
    0.f, 0.f, 0.f, 0.f};

Matrix4::Matrix4()
    : Matrix4(Matrix4::identity)
{
}

Matrix4::Matrix4(std::initializer_list<float> list)
{
    Assert::isTrue(list.size() == 4 * 4, "too many elements in the initializer list");
    auto value = list.begin();
    for(size_t x = 0; x < 4; x++)
        for(size_t y = 0; y < 4; y++)
            m[x][y] = *value++;
}

Matrix4::Matrix4(const float* m)
{
    std::memcpy(this->m, m, sizeof(this->m));
}

void Matrix4::translate(const Vector3& vec)
{
    Matrix4 mat;
    *this *= mat.setTranslation(vec);
}

void Matrix4::rotate(float angle, const Vector3& axis)
{
    if(axis == Vector3::unit_x)
        rotateX(angle);
    else if(axis == Vector3::unit_y)
        rotateY(angle);
    else if(axis == Vector3::unit_z)
        rotateZ(angle);
    else
        Assert::isTrue(false, "unknown axis");
}

void Matrix4::scale(const Vector3& vec)
{
    Matrix4 mat;
    *this *= mat.setScale(vec);
}

const float* Matrix4::data() const
{
    return &m[0][0];
}

Matrix4 Matrix4::createPerspective(float FOV, float aspectRatio, float n, float f)
{
    const float tanFOV = std::tan(FOV / 2.f);

    Matrix4 mat;
    mat.m[0][0]  = 1.f / (aspectRatio * (tanFOV / 2));
    mat.m[1][1]  = 1.f / (tanFOV / 2);
    mat.m[2][2]  = f / (f - n);
    mat.m[2][3]  = 1.f;
    mat.m[3][2]  = -(f * n) / (f - n);
    return mat;
}

Matrix4 Matrix4::createOrthographic(float zoomX, float zoomY, float nearPlane, float farPlane)
{
    return Matrix4();
}

Matrix4 Matrix4::createOrthographicOffCenter(float l, float r, float b, float t, float n, float f)
{
    Matrix4 mat;
    mat.m[0][0] = 2 / (r - l);
    mat.m[0][3] = (r + l) / (l - r);
    mat.m[1][1] = 2 / (t - b);
    mat.m[1][3] = (t + b) / (b - t);
    mat.m[2][2] = 2 / (n - f);
    mat.m[2][3] = (f + n) / (n - f);
    mat.m[3][3] = 1;
    return mat;
}

Vector3 Matrix4::translation() const
{
    return {m[3][0], m[3][1], m[3][2]};
}

Vector3 Matrix4::rotation() const
{
    return {}; // FIXME
}

Vector3 Matrix4::scale() const
{
    return {m[0][0], m[1][1], m[2][2]};
}

Matrix4& Matrix4::setTranslation(const Vector3& vec)
{
    m[3][0] = vec.x;
    m[3][1] = vec.y;
    m[3][2] = vec.z;
    return *this;
}

// FIXME: 会直接改变缩放
Matrix4& Matrix4::setRotation(float angle, const Vector3& axis)
{
    if(axis == Vector3::unit_x)
        setRotationX(angle);
    else if(axis == Vector3::unit_y)
        setRotationY(angle);
    else if(axis == Vector3::unit_z)
        setRotationZ(angle);
    else
        Assert::isTrue(false, "unknown axis");
    return *this;
}

Matrix4& Matrix4::setScale(const Vector3& vec)
{
    m[0][0] = vec.x;
    m[1][1] = vec.y;
    m[2][2] = vec.z;
    return *this;
}

Matrix4& Matrix4::setRotationX(float angle)
{
    const float sin = std::sin(angle);
    const float cos = std::cos(angle);

    m[1][1] = cos;
    m[1][2] = -sin;
    m[2][1] = sin;
    m[2][2] = cos;
    return *this;
}

Matrix4& Matrix4::setRotationY(float angle)
{
    const float sin = std::sin(angle);
    const float cos = std::cos(angle);

    m[0][0] = cos;
    m[0][2] = sin;
    m[2][0] = -sin;
    m[2][2] = cos;
    return *this;
}

Matrix4& Matrix4::setRotationZ(float angle)
{
    const float sin = std::sin(angle);
    const float cos = std::cos(angle);

    m[0][0] = cos;
    m[0][1] = -sin;
    m[1][0] = sin;
    m[1][1] = cos;
    return *this;
}

Matrix4& Matrix4::inverse()
{
    // FIXME
    return *this;
}

void Matrix4::rotateX(float angle)
{
    Matrix4 mat;
    *this *= mat.setRotationX(angle);
}

void Matrix4::rotateY(float angle)
{
    Matrix4 mat;
    *this *= mat.setRotationY(angle);
}

void Matrix4::rotateZ(float angle)
{
    Matrix4 mat;
    *this *= mat.setRotationZ(angle);
}

Matrix4 Matrix4::operator-() const
{
    Matrix4 result;
    for(size_t x = 0; x < 4; x++)
        for(size_t y = 0; y < 4; y++)
            result.m[x][y] = -m[x][y];
    return result;
}

Matrix4& Matrix4::operator=(const Matrix4& rhs)
{
    std::memcpy(m, rhs.m, sizeof(m));
    return *this;
}

Matrix4 Matrix4::operator+(const Matrix4& rhs) const
{
    return Matrix4(*this) += rhs;
}

Matrix4& Matrix4::operator+=(const Matrix4& rhs)
{
    for(size_t x = 0; x < 4; x++)
        for(size_t y = 0; y < 4; y++)
            m[x][y] += rhs.m[x][y];
    return *this;
}

Matrix4 Matrix4::operator-(const Matrix4& rhs) const
{
    return Matrix4(*this) -= rhs;
}

Matrix4& Matrix4::operator-=(const Matrix4& rhs)
{
    for(size_t x = 0; x < 4; x++)
        for(size_t y = 0; y < 4; y++)
            m[x][y] -= rhs.m[x][y];
    return *this;
}

Matrix4 Matrix4::operator*(const Matrix4& rhs) const
{
    return Matrix4(*this) *= rhs;
}

// TODO: 编写测试用例
Matrix4& Matrix4::operator*=(const Matrix4& rhs)
{
    float product[4][4] = {0};
    for(size_t i = 0; i < 4; ++i)
    {
        for(size_t k = 0; k < 4; ++k)
        {
            auto s = m[i][k];
            for(size_t j = 0; j < 4; ++j)
                product[i][j] += s * rhs.m[k][j];
        }
    }
    std::memcpy(m, product, sizeof(m));
    return *this;
}

Matrix4 Matrix4::operator*(float rhs) const
{
    return Matrix4(*this) *= rhs;
}

Matrix4& Matrix4::operator*=(float rhs)
{
    for(size_t x = 0; x < 4; x++)
        for(size_t y = 0; y < 4; y++)
            m[x][y] *= rhs;
    return *this;
}

/*
Vector4 Matrix4::operator*(const Vector4& vec) const
{
    Vector4 product;
    for(size_t i = 0; i < 4; i++)
        for(size_t j = 0; j < 4; j++)
            product[i] += m[i][j];
    return product;
}
*/

} // namespace clem