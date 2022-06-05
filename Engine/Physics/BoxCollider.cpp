// Copyright 2021 ShenMian
// License(Apache-2.0)

#include "Algorithm.hpp"

namespace phys
{

BoxCollider::BoxCollider(const Vector3& center, const Vector3& halfExtent)
	: center(center), halfExtent(halfExtent)
{
}

bool BoxCollider::intersects(const Collider& other) const
{
	return other.intersects(*this);
}

bool BoxCollider::intersects(const BoxCollider& other) const
{
	return contains(other.min()) || contains(other.max());
}

bool BoxCollider::intersects(const SphereCollider& other) const
{
	return algo::intersects(*this, other);
}

bool BoxCollider::contains(const BoxCollider& other) const
{
	return contains(other.min()) && contains(other.max());
}

bool BoxCollider::contains(const Vector3& point) const
{
	const auto max = max();
	const auto min = min();
	return min.x <= point.x && point.x <= max.x && min.y <= point.y && point.y <= max.y;
}

Vector3 BoxCollider::min() const
{
	return center - halfExtent;
}

Vector3 BoxCollider::max() const
{
	return center + halfExtent;
}

}
