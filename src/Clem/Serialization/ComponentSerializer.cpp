// Copyright 2021 SMS
// License(Apache-2.0)

/*

#include "ComponentSerializer.h"
#include "MathSerializer.h"
#include "Clem/Component/Tag.h"
#include "Clem/Component/Transform.h"
#include "Clem/Physics/Rigidbody.h"
#include "Clem/Renderer/Sprite.h"

YAML::Emitter& operator<<(YAML::Emitter& o, const Tag& t)
{
	o << YAML::Key << "Tag" << YAML::Value << t.tag;
	return o;
}

YAML::Emitter& operator<<(YAML::Emitter& o, const Transform& t)
{
	o << YAML::Key << "Tag" << YAML::Value;
	o << YAML::Flow << YAML::BeginSeq << t.position << t.rotation << YAML::EndSeq;
	return o;
}

YAML::Emitter& operator<<(YAML::Emitter& o, const Tile& t)
{
	o << YAML::Flow;
	o << YAML::BeginSeq << t.ch << t.color.fore << t.color.back << YAML::EndSeq;
	return o;
}

YAML::Emitter& operator<<(YAML::Emitter& o, const Sprite& s)
{
	o << YAML::Key << "Sprite" << YAML::Value;
	return o;
}

YAML::Emitter& operator<<(YAML::Emitter& o, const Rigidbody& b)
{
	o << YAML::Key << "Rigidbody" << YAML::Value;
	o << YAML::Flow << YAML::BeginSeq << b.velocity << b.acceleration << YAML::EndSeq;
	return o;
}

*/
