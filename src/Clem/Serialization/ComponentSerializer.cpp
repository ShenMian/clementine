// Copyright 2021 SMS
// License(Apache-2.0)

#include "ComponentSerializer.h"

YAML::Emitter& operator<<(YAML::Emitter& o, const Tag& t)
{
	return o;
}
