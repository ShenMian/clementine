// Copyright 2021 SMS
// License(Apache-2.0)

#ifndef CLEM_SERIALIZATION_COMPONENT_SERIALIZER_H_
#define CLEM_SERIALIZATION_COMPONENT_SERIALIZER_H_

#include "yaml-cpp/yaml.h"

class Tag;
class Transform;
class Sprite;
class Rigidbody;

YAML::Emitter& operator<<(YAML::Emitter& out, const Tag& tag);
YAML::Emitter& operator<<(YAML::Emitter& out, const Transform& tag);
YAML::Emitter& operator<<(YAML::Emitter& out, const Sprite& tag);
YAML::Emitter& operator<<(YAML::Emitter& out, const Rigidbody& tag);

#endif // !CLEM_SERIALIZATION_COMPONENT_SERIALIZER_H_
