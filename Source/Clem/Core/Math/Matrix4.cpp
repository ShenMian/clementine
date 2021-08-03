// Copyright 2021 SMS
// License(Apache-2.0)

#include "Matrix4.h"
#include "Vector3.h"
#include "Assert.hpp"
#include <cmath>
#include <cstring>

const Matrix4 Matrix4::identity = {
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f};

const Matrix4 Matrix4::zero = {
    0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f};

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
    Matrix4 mat(Matrix4::identity);
    mat.m[3][0] = vec.x;
    mat.m[3][1] = vec.y;
    mat.m[3][2] = vec.z;
    *this *= mat;
}

void Matrix4::rotate(float angle, Vector3& axis)
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
    Matrix4 mat(Matrix4::identity);
    mat.m[0][0] = vec.x;
    mat.m[1][1] = vec.y;
    mat.m[2][2] = vec.z;
    *this *= mat;
}

const float* Matrix4::data() const
{
    return &m[0][0];
}

void Matrix4::rotateX(float angle)
{
    const float sin = std::sin(angle);
    const float cos = std::cos(angle);

    Matrix4 mat(Matrix4::identity);
    m[1][1] = cos;
    m[1][2] = -sin;
    m[2][1] = sin;
    m[2][2] = cos;
    *this *= mat;
}

void Matrix4::rotateY(float angle)
{
    const float sin = std::sin(angle);
    const float cos = std::cos(angle);

    Matrix4 mat(Matrix4::identity);
    m[0][0] = cos;
    m[0][2] = sin;
    m[2][0] = -sin;
    m[2][2] = cos;
    *this *= mat;
}

void Matrix4::rotateZ(float angle)
{
    const float sin = std::sin(angle);
    const float cos = std::cos(angle);

    Matrix4 mat(Matrix4::identity);
    m[0][0] = cos;
    m[0][1] = -sin;
    m[1][0] = sin;
    m[1][1] = cos;
    *this *= mat;
}

Vector3 Matrix4::translation() const
{
    return {m[3][0], m[3][1], m[3][2]};
}

Vector3 Matrix4::rotation() const
{
    return {}; // TODO
}

Vector3 Matrix4::scale() const
{
    return {m[0][0], m[1][1], m[2][2]};
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