// Copyright 2021 ShenMian
// License(Apache-2.0)

#pragma once

#include "Collider.h"

namespace phys
{

class SphereCollider : public Collider
{
public:
	bool intersects(const SphereCollider& other) const;

	bool contains(const SphereCollider& other) const;

	bool contains(const Vector3& point) const;

	Vector3 center;
	float radius;
};

}

#include "SphereCollider.inl"
