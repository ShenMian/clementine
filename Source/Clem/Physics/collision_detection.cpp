
#include "Clem.h"

using namespace clem;

/**
 * @brief ¶þÎ¬Ïß¶Î.
 */
struct Line2
{
	Point2 start;
	Point2 end;
};

bool collision(Line2 l, Point2 p)
{
	const auto dx = l.end.x - l.start.x;
	const auto dy = l.end.y - l.start.y;
	assert(dx != 0 && dy != 0);
	const auto k  = dy / dx;
	const auto b = l.start.y; // b = l.end.y - k * l.end.x

	return p.y == k * p.x + b;
}

bool collision(BoxCollider b, Point2 p)
{
	return b.getRect().intersectsPoint(p);
}

// TODO: CircleCollider::getCenter();
bool collision(CircleCollider c, Point2 p)
{
	const auto center = c.getPosition();
	return center.distanceSquared(p) <= c.getRadius() * c.getRadius();
}

bool collision(BoxCollider a, BoxCollider b)
{
	return a.getRect().intersectsRect(b.getRect());
}

bool collision(CircleCollider a, CircleCollider b)
{
	const auto aCenter = a.getPosition();
	const auto bCenter = b.getPosition();
	return aCenter.distance(bCenter) <= a.getRadius() + b.getRadius();
}

bool collision(CircleCollider c, Line2 l)
{
	const auto center        = c.getPosition();
	const auto startToCenter = center - l.start;

	const auto startToEnd = l.end - l.start;

	const auto t = startToCenter.dot(startToEnd) / startToEnd.dot(startToEnd);

	if(t < 0.0f || t > 1.0f)
		return false;

	const auto closestPoint = l.start + startToEnd * t;

	collision(c, closestPoint);
}
