// Copyright 2021 SMS
// License(Apache-2.0)

#include "Matrix4.h"
#include "Core/Assert.hpp"
#include "Vector3.h"
#include "Vector4.h"
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

Matrix4::Matrix4(float v)
    : Matrix4(identity * v)
{
    Assert::isTrue(identity != zero, "Do not declare a matrix as a static global variable");
}

Matrix4::Matrix4(const Matrix4& mat)
    : Matrix4(mat.data())
{
}

Matrix4::Matrix4(std::initializer_list<float> list)
{
    Assert::isTrue(list.size() == 4 * 4, "incorrect number of elements");
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
    *this *= createTranslation(vec);
}

void Matrix4::rotate(float angle, const Vector3& axis)
{
    *this *= createRotation(angle, axis);
}

void Matrix4::scale(const Vector3& vec)
{
    *this *= createScale(vec);
}

const float* Matrix4::data() const
{
    return &m[0][0];
}

float* Matrix4::data()
{
    return &m[0][0];
}

Vector3 Matrix4::forword() const
{
    return {-m[2][0], -m[2][1], -m[2][2]};
}

Vector3 Matrix4::back() const
{
    return -forword();
}

Vector3 Matrix4::left() const
{
    return {-m[0][0], -m[0][1], -m[0][2]};
}

Vector3 Matrix4::right() const
{
    return -left();
}

Vector3 Matrix4::up() const
{
    return {m[1][0], m[1][1], m[1][2]};
}

Vector3 Matrix4::down() const
{
    return -up();
}

Vector3 Matrix4::translate() const
{
    return {m[3][0], m[3][1], m[3][2]};
}

Vector3 Matrix4::rotate() const
{
    return {}; // FIXME: 完善实现
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

Matrix4 Matrix4::createTranslation(const Vector3& pos)
{
    Matrix4 mat = Matrix4::identity;
    mat[3][0]   = pos.x;
    mat[3][1]   = pos.y;
    mat[3][2]   = pos.z;
    return mat;
}

Matrix4 Matrix4::createRotation(float angle, const Vector3& axis)
{
#if 1
    const float c = std::cos(angle);
    const float s = std::sin(angle);
    const float t = 1.f - c;

    Vector3     normal = axis.getNormalized();
    const float x      = normal.x;
    const float y      = normal.y;
    const float z      = normal.z;

    Matrix4 mat;
    mat.m[0][0] = 1 + t * (x * x - 1);
    mat.m[0][1] = z * s + t * x * y;
    mat.m[0][2] = -y * s + t * x * z;
    mat.m[0][3] = 0.0f;

    mat.m[1][0] = -z * s + t * x * y;
    mat.m[1][1] = 1 + t * (y * y - 1);
    mat.m[1][2] = x * s + t * y * z;
    mat.m[1][3] = 0.0f;

    mat.m[2][0] = y * s + t * x * z;
    mat.m[2][1] = -x * s + t * y * z;
    mat.m[2][2] = 1 + t * (z * z - 1);
    mat.m[2][3] = 0.0f;

    mat.m[3][0] = 0.0f;
    mat.m[3][1] = 0.0f;
    mat.m[3][2] = 0.0f;
    mat.m[3][3] = 1.0f;
    return mat;
#else
    const auto  normal = axis.getNormalized();
    const float x      = normal.x;
    const float y      = normal.y;
    const float z      = normal.z;

    const float sin = std::sin(angle);
    const float cos = std::cos(angle);

    float t   = 1.0f - cos;
    float tx  = t * x;
    float ty  = t * y;
    float tz  = t * z;
    float txy = tx * y;
    float txz = tx * z;
    float tyz = ty * z;
    float sx  = sin * x;
    float sy  = sin * y;
    float sz  = sin * z;

    Matrix4 mat;
    mat.m[0][0] = cos + tx * x;
    mat.m[0][1] = txy + sz;
    mat.m[0][2] = txz - sy;
    mat.m[0][3] = 0.0f;

    mat.m[1][0] = txy - sz;
    mat.m[1][1] = cos + ty * y;
    mat.m[1][2] = tyz + sx;
    mat.m[1][3] = 0.0f;

    mat.m[2][0] = txz + sy;
    mat.m[2][1] = tyz - sx;
    mat.m[2][2] = cos + tz * z;
    mat.m[2][3] = 0.0f;

    mat.m[3][0] = 0.0f;
    mat.m[3][1] = 0.0f;
    mat.m[3][2] = 0.0f;
    mat.m[3][3] = 1.0f;
    return mat;
#endif
}

Matrix4 Matrix4::createScale(const Vector3& scale)
{
    Matrix4 mat = Matrix4::identity;
    mat.m[0][0] = scale.x;
    mat.m[1][1] = scale.y;
    mat.m[2][2] = scale.z;
    return mat;
}

Matrix4 Matrix4::createRotationX(float angle)
{
    const float sin = std::sin(angle);
    const float cos = std::cos(angle);

    Matrix4 mat = Matrix4::identity;
    mat.m[1][1] = cos;
    mat.m[1][2] = sin;
    mat.m[2][1] = -sin;
    mat.m[2][2] = cos;
    return mat;
}

Matrix4 Matrix4::createRotationY(float angle)
{
    const float sin = std::sin(angle);
    const float cos = std::cos(angle);

    Matrix4 mat = Matrix4::identity;
    mat.m[0][0] = cos;
    mat.m[0][2] = sin;
    mat.m[2][0] = -sin;
    mat.m[2][2] = cos;
    return mat;
}

Matrix4 Matrix4::createRotationZ(float angle)
{
    const float sin = std::sin(angle);
    const float cos = std::cos(angle);

    Matrix4 mat = Matrix4::identity;
    mat.m[0][0] = cos;
    mat.m[0][1] = sin;
    mat.m[1][0] = -sin;
    mat.m[1][1] = cos;
    return mat;
}

Matrix4 Matrix4::createPerspective(float FOV, float aspectRatio, float n, float f)
{
    Assert::isTrue(std::abs(aspectRatio - std::numeric_limits<float>::epsilon()) > 0.0f);
    Assert::isTrue(aspectRatio != 0 && n != f);

#if 1 // v
    const float tanHalfFOV = std::tan(FOV / 2.f);

    Matrix4 mat;
    mat.m[0][0] = 1.f / (aspectRatio * tanHalfFOV);
    mat.m[1][1] = 1.f / tanHalfFOV;
    mat.m[2][2] = f / (f - n);
    mat.m[2][3] = 1.f;
    mat.m[3][2] = -(f * n) / (f - n);
    return mat;
#else // c
    float f_n   = 1.0f / (f - n);
    float theta = FOV * 0.5f;

    float divisor = std::tan(theta);
    float factor  = 1.0f / divisor;

    Matrix4 mat(0.f);
    mat.m[0][0] = (1.0f / aspectRatio) * factor;
    mat.m[1][1] = factor;
    mat.m[2][2] = (-(f + n)) * f_n;
    mat.m[2][3] = -1.0f;
    mat.m[3][2] = -2.0f * f * n * f_n;
    return mat;
#endif
}

Matrix4 Matrix4::createOrthographic(float w, float h, float n, float f)
{
    return createOrthographicOffCenter(-w / 2, w / 2, -h / 2, h / 2, n, f);
}

Matrix4 Matrix4::createOrthographicOffCenter(float l, float r, float b, float t, float n, float f)
{
    Assert::isTrue(l != r && b != t && n != f);

#if 0 // v
    Matrix4 mat;
    mat.m[0][0] = 2.f / (r - l);
    mat.m[1][1] = 2.f / (b - t);
    mat.m[2][2] = 1.f / (f - n);
    mat.m[3][0] = -(r + l) / (r - l);
    mat.m[3][1] = -(b + t) / (b - t);
    mat.m[3][2] = -n / (f - n);
    return mat;
#else // c
    Matrix4 mat(0.f);
    mat.m[0][0] = 2 / (r - l);
    mat.m[1][1] = 2 / (t - b);
    mat.m[2][2] = 2 / (n - f);
    mat.m[3][0] = (l + r) / (l - r);
    mat.m[3][1] = (t + b) / (b - t);
    mat.m[3][2] = (n + f) / (n - f);
    mat.m[3][3] = 1;
    return mat;
#endif
}

float* Matrix4::operator[](size_t row)
{
    return m[row];
}

const float* Matrix4::operator[](size_t row) const
{
    return m[row];
}

float Matrix4::determinant() const
{
    float a0 = m[0][0] * m[1][1] - m[0][1] * m[1][0];
    float a1 = m[0][0] * m[1][2] - m[0][2] * m[1][0];
    float a2 = m[0][0] * m[1][3] - m[0][3] * m[1][0];
    float a3 = m[0][1] * m[1][2] - m[0][2] * m[1][1];
    float a4 = m[0][1] * m[1][3] - m[0][3] * m[1][1];
    float a5 = m[0][2] * m[1][3] - m[0][3] * m[1][2];
    float b0 = m[2][0] * m[3][1] - m[2][1] * m[3][0];
    float b1 = m[2][0] * m[3][2] - m[2][2] * m[3][0];
    float b2 = m[2][0] * m[3][3] - m[2][3] * m[3][0];
    float b3 = m[2][1] * m[3][2] - m[2][2] * m[3][1];
    float b4 = m[2][1] * m[3][3] - m[2][3] * m[3][1];
    float b5 = m[2][2] * m[3][3] - m[2][3] * m[3][2];

    return a0 * b5 - a1 * b4 + a2 * b3 + a3 * b2 - a4 * b1 + a5 * b0;
}

Matrix4& Matrix4::inverse()
{
    float a0 = m[0][0] * m[1][1] - m[0][1] * m[1][0];
    float a1 = m[0][0] * m[1][2] - m[0][2] * m[1][0];
    float a2 = m[0][0] * m[1][3] - m[0][3] * m[1][0];
    float a3 = m[0][1] * m[1][2] - m[0][2] * m[1][1];
    float a4 = m[0][1] * m[1][3] - m[0][3] * m[1][1];
    float a5 = m[0][2] * m[1][3] - m[0][3] * m[1][2];
    float b0 = m[2][0] * m[3][1] - m[2][1] * m[3][0];
    float b1 = m[2][0] * m[3][2] - m[2][2] * m[3][0];
    float b2 = m[2][0] * m[3][3] - m[2][3] * m[3][0];
    float b3 = m[2][1] * m[3][2] - m[2][2] * m[3][1];
    float b4 = m[2][1] * m[3][3] - m[2][3] * m[3][1];
    float b5 = m[2][2] * m[3][3] - m[2][3] * m[3][2];

    float det = a0 * b5 - a1 * b4 + a2 * b3 + a3 * b2 - a4 * b1 + a5 * b0;

    // 接近 0, 无法求逆.
    // det = determinant();
    if(det <= 2e-37f)
        return *this;

    Matrix4 inverse;
    inverse.m[0][0] = m[1][1] * b5 - m[1][2] * b4 + m[1][3] * b3;
    inverse.m[0][1] = -m[0][1] * b5 + m[0][2] * b4 - m[0][3] * b3;
    inverse.m[0][2] = m[3][1] * a5 - m[3][2] * a4 + m[3][3] * a3;
    inverse.m[0][3] = -m[2][1] * a5 + m[2][2] * a4 - m[2][3] * a3;

    inverse.m[1][0] = -m[1][0] * b5 + m[1][2] * b2 - m[1][3] * b1;
    inverse.m[1][1] = m[0][0] * b5 - m[0][2] * b2 + m[0][3] * b1;
    inverse.m[1][2] = -m[3][0] * a5 + m[3][2] * a2 - m[3][3] * a1;
    inverse.m[1][3] = m[2][0] * a5 - m[2][2] * a2 + m[2][3] * a1;

    inverse.m[2][0] = m[1][0] * b4 - m[1][1] * b2 + m[1][3] * b0;
    inverse.m[2][1] = -m[0][0] * b4 + m[0][1] * b2 - m[0][3] * b0;
    inverse.m[2][2] = m[3][0] * a4 - m[3][1] * a2 + m[3][3] * a0;
    inverse.m[2][3] = -m[2][0] * a4 + m[2][1] * a2 - m[2][3] * a0;

    inverse.m[3][0] = -m[1][0] * b3 + m[1][1] * b1 - m[1][2] * b0;
    inverse.m[3][1] = m[0][0] * b3 - m[0][1] * b1 + m[0][2] * b0;
    inverse.m[3][2] = -m[3][0] * a3 + m[3][1] * a1 - m[3][2] * a0;
    inverse.m[3][3] = m[2][0] * a3 - m[2][1] * a1 + m[2][2] * a0;

    return *this = inverse * (1.f / det);
}

Matrix4 Matrix4::getInversed() const
{
    Matrix4 mat(*this);
    mat.inverse();
    return mat;
}

void Matrix4::transpose()
{
#if 1
    Matrix4 mat = {
        m[0][0],
        m[1][0],
        m[2][0],
        m[3][0],

        m[0][1],
        m[1][1],
        m[2][1],
        m[0][1],

        m[1][2],
        m[2][2],
        m[3][2],
        m[3][2],

        m[1][3],
        m[2][3],
        m[3][3],
        m[3][3]};
#else
    Matrix4 mat;
    for(size_t i = 0; i < 4; i++)
    {
        for(size_t j = 0; j < 4; j++)
        {
            mat.m[j][i] = m[i][j];
        }
    }
#endif
    *this = mat;
}

Matrix4 Matrix4::getTransposed() const
{
    Matrix4 mat(*this);
    mat.transpose();
    return mat;
}

void Matrix4::rotateX(float angle)
{
    *this *= createRotationX(angle);
}

void Matrix4::rotateY(float angle)
{
    *this *= createRotationY(angle);
}

void Matrix4::rotateZ(float angle)
{
    *this *= createRotationZ(angle);
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
#if 1
    Matrix4 mat;
    mat[0][0] = m[0][0] * rhs[0][0] + m[1][0] * rhs[0][1] + m[2][0] * rhs[0][2] + m[3][0] * rhs[0][3];
    mat[0][1] = m[0][1] * rhs[0][0] + m[1][1] * rhs[0][1] + m[2][1] * rhs[0][2] + m[3][1] * rhs[0][3];
    mat[0][2] = m[0][2] * rhs[0][0] + m[1][2] * rhs[0][1] + m[2][2] * rhs[0][2] + m[3][2] * rhs[0][3];
    mat[0][3] = m[0][3] * rhs[0][0] + m[1][3] * rhs[0][1] + m[2][3] * rhs[0][2] + m[3][3] * rhs[0][3];

    mat[1][0] = m[0][0] * rhs[1][0] + m[1][0] * rhs[1][1] + m[2][0] * rhs[1][2] + m[3][0] * rhs[1][3];
    mat[1][1] = m[0][1] * rhs[1][0] + m[1][1] * rhs[1][1] + m[2][1] * rhs[1][2] + m[3][1] * rhs[1][3];
    mat[1][2] = m[0][2] * rhs[1][0] + m[1][2] * rhs[1][1] + m[2][2] * rhs[1][2] + m[3][2] * rhs[1][3];
    mat[1][3] = m[0][3] * rhs[1][0] + m[1][3] * rhs[1][1] + m[2][3] * rhs[1][2] + m[3][3] * rhs[1][3];

    mat[2][0] = m[0][0] * rhs[2][0] + m[1][0] * rhs[2][1] + m[2][0] * rhs[2][2] + m[3][0] * rhs[2][3];
    mat[2][1] = m[0][1] * rhs[2][0] + m[1][1] * rhs[2][1] + m[2][1] * rhs[2][2] + m[3][1] * rhs[2][3];
    mat[2][2] = m[0][2] * rhs[2][0] + m[1][2] * rhs[2][1] + m[2][2] * rhs[2][2] + m[3][2] * rhs[2][3];
    mat[2][3] = m[0][3] * rhs[2][0] + m[1][3] * rhs[2][1] + m[2][3] * rhs[2][2] + m[3][3] * rhs[2][3];

    mat[3][0] = m[0][0] * rhs[3][0] + m[1][0] * rhs[3][1] + m[2][0] * rhs[3][2] + m[3][0] * rhs[3][3];
    mat[3][1] = m[0][1] * rhs[3][0] + m[1][1] * rhs[3][1] + m[2][1] * rhs[3][2] + m[3][1] * rhs[3][3];
    mat[3][2] = m[0][2] * rhs[3][0] + m[1][2] * rhs[3][1] + m[2][2] * rhs[3][2] + m[3][2] * rhs[3][3];
    mat[3][3] = m[0][3] * rhs[3][0] + m[1][3] * rhs[3][1] + m[2][3] * rhs[3][2] + m[3][3] * rhs[3][3];
    *this     = mat;
#else
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
#endif
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