// Copyright 2021 ShenMian
// License(Apache-2.0)

#include "Algorithm.hpp"

namespace phys
{

inline bool SphereCollider::intersects(const Collider& other) const
{
	return other.intersects(*this);
}

inline bool SphereCollider::intersects(const SphereCollider& other) const
{
	const auto disSq = (center - other.center).normSq();
	const auto minDisSq = (radius + other.radius) * (radius + other.radius);
	return disSq <= minDisSq;
}

inline bool SphereCollider::intersects(const BoxCollider& other) const
{
	return algo::intersects(*this, other);
}

inline bool SphereCollider::contains(const SphereCollider& other) const
{
	return (center - other.center).norm() + other.radius < radius;
}

inline bool SphereCollider::contains(const Vector3& point) const
{
	return (center - point).normSq() <= radius * radius;
}

}
