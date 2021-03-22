// Copyright 2021 SMS
// License(Apache-2.0)

#ifndef CLEM_SERIALIZATION_MATH_SERIALIZER_H_
#define CLEM_SERIALIZATION_MATH_SERIALIZER_H_

#include "yaml-cpp/yaml.h"

class Vec2;
class Rect;

YAML::Emitter& operator<<(YAML::Emitter& out, const Vec2& tag);
YAML::Emitter& operator<<(YAML::Emitter& out, const Rect& tag);

#endif // !CLEM_SERIALIZATION_MATH_SERIALIZER_H_
