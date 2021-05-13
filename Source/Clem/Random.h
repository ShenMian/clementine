// Copyright 2021 SMS
// License(Apache-2.0)
// 随机数生成器

#pragma once

#include "Clem/Core/Math/Math.h"
#include <random>
#include <stdint.h>

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
	float getFloat(float min = 0.0f, float max = 1.0f);

	/**
	 * @brief 生成指定范围内的随机二维点.
	 */
	Point2 getPoint2(const Point2& min, const Point2& max);

	/**
	 * @brief 生成指定范围内的随机二维点.
	 */
	Point2i getPoint2i(const Point2i& min, const Point2i& max);

private:
	std::mt19937 generator;
};
