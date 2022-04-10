// Copyright 2021 ShenMian
// License(Apache-2.0)

#pragma once

#include "Collider.h"

namespace phys
{

class BoxCollider;

class SphereCollider : public Collider
{
public:
	bool intersects(const Collider& other) const;
	bool intersects(const SphereCollider& other) const;
	bool intersects(const BoxCollider& other) const;

	bool contains(const SphereCollider& other) const;
	bool contains(const Vector3& point) const;

	Vector3 center;
	float radius;
};

}
