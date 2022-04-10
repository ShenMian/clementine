// Copyright 2021 ShenMian
// License(Apache-2.0)

#include "Algorithm.hpp"

namespace phys
{

inline bool BoxCollider::intersects(const Collider& other) const
{
	return other.intersects(*this);
}

inline bool BoxCollider::intersects(const BoxCollider& other) const
{
	return contains(other.getMin()) || contains(other.getMax());
}

inline bool BoxCollider::intersects(const SphereCollider& other) const
{
	return algo::intersects(*this, other);
}

inline bool BoxCollider::contains(const BoxCollider& other) const
{
	return contains(other.getMin()) && contains(other.getMax());
}

inline bool BoxCollider::contains(const Vector3& point) const
{
	const auto max = getMax();
	const auto min = getMin();
	return min.x <= point.x && point.x <= max.x && min.y <= point.y && point.y <= max.y;
}

inline Vector3 BoxCollider::getMin() const
{
	return center - halfExtent;
}

inline Vector3 BoxCollider::getMax() const
{
	return center + halfExtent;
}

}
