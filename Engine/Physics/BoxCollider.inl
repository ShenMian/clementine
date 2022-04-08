// Copyright 2021 ShenMian
// License(Apache-2.0)

namespace phys
{

bool BoxCollider::intersects(const BoxCollider& other) const
{
	return contains(other.getMin()) || contains(other.getMax());
}

bool BoxCollider::contains(const BoxCollider& other) const
{
	return contains(other.getMin()) && contains(other.getMax());
}

bool BoxCollider::contains(const Vector3& point) const
{
	const auto max = getMax();
	const auto min = getMin();
	return min.x <= point.x && point.x <= max.x && min.y <= point.y && point.y <= max.y;
}

Vector3 BoxCollider::getMin() const
{
	return center - halfExtent;
}

Vector3 BoxCollider::getMax() const
{
	return center + halfExtent;
}

}
