// Copyright 2021 ShenMian
// License(Apache-2.0)

#pragma once

#include "Collider.h"
#include <Math/Math.hpp>

namespace phys
{

class SphereCollider;

class BoxCollider : public Collider
{
public:
	bool intersects(const Collider& other) const;
	bool intersects(const BoxCollider& other) const;
	bool intersects(const SphereCollider& other) const;

	bool contains(const BoxCollider& other) const;
	bool contains(const Vector3& point) const;

	Vector3 getMin() const;
	Vector3 getMax() const;

	Vector3 center;
	Vector3 halfExtent;
};

}
