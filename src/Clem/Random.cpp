﻿// Copyright 2021 SMS
// License(Apache-2.0)

#include "Random.h"

using std::uniform_int_distribution;
using std::uniform_real_distribution;

Random::Random()
{
	generator.seed(std::random_device()());
}

void Random::seed(uint32_t seed)
{
	generator.seed(seed);
}

uint32_t Random::getUint32(uint32_t min, uint32_t max)
{
	uniform_int_distribution<uint32_t> dist(min, max);
	return dist(generator);
}

int32_t Random::getInt32(int32_t min, int32_t max)
{
	uniform_int_distribution<int32_t> dist(min, max);
	return dist(generator);
}

float Random::getFloat()
{
	uniform_real_distribution<float> dist;
	return dist(generator);
}

Point<float> Random::getPoint(const Point<float>& min, const Point<float>& max)
{
	return Point<float>(getInt32(min.x, max.x), getInt32(min.y, max.y));
}
