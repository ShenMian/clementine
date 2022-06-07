// Copyright 2021 ShenMian
// License(Apache-2.0)

#pragma once

#include "Collider.h"
#include <Math/Math.hpp>

namespace phys
{

class SphereCollider;
class BoxCollider;

class CapsuleCollider : public Collider
{
public:
	CapsuleCollider(const Vector3& center, float radius, float height);

	bool intersects(const Collider& other) const;
	bool intersects(const SphereCollider& other) const;
	bool intersects(const BoxCollider& other) const;

	bool contains(const Vector3& point) const;

	Vector3 center;
	float radius;
	float height;
};

}
