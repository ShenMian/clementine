// Copyright 2021 SMS
// License(Apache-2.0)

#include "MathSerializer.h"
#include "Clem/Math/Vec2.h"
#include "Clem/Math/Rect.h"

YAML::Emitter& operator<<(YAML::Emitter& o, const Vec2& v)
{
	o << YAML::Flow;
	o << YAML::BeginSeq << v.x << v.y << YAML::EndSeq;
	return o;
}

YAML::Emitter& operator<<(YAML::Emitter& o, const Rect& r)
{
	o << YAML::Flow;
	o << YAML::BeginSeq << r.origin << r.size << YAML::EndSeq;
	return o;
}
