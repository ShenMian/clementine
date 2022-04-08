// Copyright 2021 ShenMian
// License(Apache-2.0)

namespace phys
{

bool SphereCollider::intersects(const SphereCollider& other) const
{
	const auto disSq = (center - other.center).normSq();
	const auto minDisSq = radius * radius + other.radius * other.radius;
	return disSq <= minDisSq;
}

bool SphereCollider::contains(const SphereCollider& other) const
{
	return (other.center - center).norm() + other.radius < radius;
}

bool SphereCollider::contains(const Vector3& point) const
{
	return (point - center).normSq() <= radius * radius;
}

}
