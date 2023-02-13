// Copyright 2023 ShenMian
// License(Apache-2.0)

#pragma once

#include "collider.hpp"
#include "core/type_index.hpp"

namespace phys
{

struct SphereCollider : public Collider
{
	DECLARE_TYPE

	float radius;
};

} // namespace phys
