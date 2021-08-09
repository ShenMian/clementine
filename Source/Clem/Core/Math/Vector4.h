// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <cfloat>
#include <cmath>

namespace clem
{

class Vector3;

/**
 * @addtogroup Math
 * @{
 */

/**
 * @brief 四维向量, 单精度浮点数.
 */
class Vector4
{
public:
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    float w = 0.0f;

    /**
	 * @brief 默认构造函数.
	 */
    Vector4() = default;

    /**
	 * @brief 构造函数.
	 *
	 * @param x x坐标.
	 * @param y y坐标.
	 * @param z z坐标.
	 */
    Vector4(float x, float y, float z, float w = 0.0f);

    /**
	 * @brief 构造函数.
	 *
	 * @param v 二维向量.
	 */
    Vector4(const Vector3& v, float w = 0.0f);
};

using Vec4 = Vector4;

/**
 * end of Math group
 * @}
 */

} // namespace clem