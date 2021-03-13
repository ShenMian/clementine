// Copyright 2021 SMS
// License(Apache-2.0)
// 随机数生成器

#include "random.h"

using std::uniform_int_distribution;

void Random::seed(uint32_t seed)
{
	generator.seed(seed);
}

uint32_t Random::uint32(uint32_t min, uint32_t max)
{
	uniform_int_distribution<uint32_t> dist(min, max);
	return dist(generator);
}

int32_t Random::int32(int32_t min, int32_t max)
{
	uniform_int_distribution<int32_t> dist(min, max);
	return dist(generator);
}
