// Copyright 2021 ShenMian
// License(Apache-2.0)

#include "CapsuleCollider.h"
#include "Algorithm.hpp"

namespace phys
{

CapsuleCollider::CapsuleCollider(const Vector3& center, float radius, float height)
	: center(center), radius(radius), height(height)
{
}

bool CapsuleCollider::intersects(const Collider& other) const
{
	return other.intersects(*this);
}

bool CapsuleCollider::intersects(const SphereCollider& other) const
{
	return false;
}

bool CapsuleCollider::intersects(const BoxCollider& other) const
{
	return false;
}

bool CapsuleCollider::contains(const Vector3& point) const
{
	return false;
}

}
