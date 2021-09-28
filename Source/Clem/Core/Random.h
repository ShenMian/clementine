// Copyright 2021 SMS
// License(Apache-2.0)
// 随机数生成器

#pragma once

#include "Core/Math/Math.h"
#include <random>
#include <stdint.h>

namespace clem
{

/**
 * @brief 伪随机数生成器.
 * 生成均匀分布的随机数.
 */
class Random
{
public:
    /**
	 * @brief 默认构造函数. 使用随机生成的种子.
	 */
    Random();

    /**
	 * @brief 设置种子.
	 */
    void setSeed(uint32_t seed);

    /**
	 * @brief 生成指定范围内的32位随机无符号整数.
	 *
	 * @param min 范围下限, 包含, 默认值: 32位无符号整数最大值.
	 * @param max 范围上限, 包含, 默认值: 0.
	 */
    uint32_t getUint32(uint32_t min = 0, uint32_t max = UINT32_MAX);

    /**
	 * @brief 生成指定范围内的32位随机有符号整数.
	 *
	 * @param min 范围下限, 包含, 默认值: 32位无符号整数最大值.
	 * @param max 范围上限, 包含, 默认值: 32位无符号整数最小值.
	 * @return int32_t
	 */
    int32_t getInt32(int32_t min = INT32_MIN, int32_t max = INT32_MAX);

    /**
	 * @brief 生成指定范围内的随机单精度浮点数.
	 *
	 * @param min 范围下限, 包含, 默认值: 0.
	 * @param max 范围上限, 包含, 默认值: 1.
	 */
    float getFloat(float min = 0.f, float max = 1.f);

    /**
	 * @brief 生成指定范围内的随机二维点.
	 *
	 * @param min 范围下限.
	 * @param max 范围上限.
	 */
    Point2 getVector2(const Vector2& min, const Vector2& max);

    /**
	 * @brief 生成指定范围内的随机二维点.
	 *
	 * @param min 范围下限.
	 * @param max 范围上限.
	 */
    Point2i getVector2i(const Vector2i& min, const Vector2i& max);

    /**
	 * @brief 生成指定范围内的随机三维点.
	 *
	 * @param min 范围下限.
	 * @param max 范围上限.
	 */
    Point3 getVector3(const Vector3& min, const Vector3& max);

private:
    std::mt19937 generator;
};

} // namespace clem