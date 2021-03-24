// Copyright 2021 SMS
// License(Apache-2.0)
// 随机数生成器

#ifndef CLEM_RANDOM_H_
#define CLEM_RANDOM_H_

#include "Clem/Core/Math/Vec2.h"
#include <random>
#include <stdint.h>

/**
 * 随机数生成器.
 */
class Random
{
public:
	Random();

	void seed(uint32_t);

	uint32_t getUint32(uint32_t min = 0, uint32_t max = UINT32_MAX);
	int32_t  getInt32(int32_t min = INT32_MIN, int32_t max = INT32_MAX);
	float    getFloat();

	Point<float> getPoint(const Point<float>& min, const Point<float>& max);

private:
	std::mt19937 generator;
};

#endif // !CLEM_RANDOM_H_
