// Copyright 2021 SMS
// License(Apache-2.0)

#include "Core/Random.h"

using std::uniform_int_distribution;
using std::uniform_real_distribution;

namespace clem
{

Random::Random()
{
    setSeed(std::random_device()());
}

void Random::setSeed(uint32_t seed)
{
    generator.seed(seed);
}

uint32_t Random::getUint32(uint32_t min, uint32_t max)
{
    uniform_int_distribution dist(min, max);
    return dist(generator);
}

int32_t Random::getInt32(int32_t min, int32_t max)
{
    uniform_int_distribution dist(min, max);
    return dist(generator);
}

float Random::getFloat(float min, float max)
{
    uniform_real_distribution dist(min, max);
    return dist(generator);
}

Point2 Random::getPoint2(const Point2& min, const Point2& max)
{
    return Point2(getFloat(min.x, max.x), getFloat(min.y, max.y));
}

Point2i Random::getPoint2i(const Point2i& min, const Point2i& max)
{
    return Point2i(getInt32(min.x, max.x), getInt32(min.y, max.y));
}

Point3 Random::getPoint3(const Point3& min, const Point3& max)
{
    return Point3(getFloat(min.x, max.x), getFloat(min.y, max.y), getFloat(min.z, max.z));
}

} // namespace clem