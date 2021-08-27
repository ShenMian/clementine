// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

constexpr float pi         = 3.14159265358979323846f;
constexpr float deg_to_rad = pi / 180;
constexpr float rad_to_deg = 180 / pi;

namespace clem
{

float radians(float degrees);
float degrees(float radians);

inline float radians(float degrees)
{
    return degrees * deg_to_rad;
}

inline float degrees(float radians)
{
    return radians * rad_to_deg;
}

} // namespace clem

#include "Matrix4.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

#include "Rect2.h"
#include "Rect2i.h"
#include "Vector2i.h"
