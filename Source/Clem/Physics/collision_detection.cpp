
#include "Clem.h"

using namespace clem;

/**
 * @brief 二维线段.
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

bool collision(BoxCollider box, Line2 l)
{
	const auto rect = box.getRect();

	const auto dx = l.end.x - l.start.x;
	const auto dy = l.end.y - l.start.y;
	assert(dx != 0 && dy != 0);
	const auto k = dy / dx;
	const auto b = l.start.y;

	// 判断是否与左边相交
	auto y = k * rect.left() + b;
	if(rect.bottom() <= y && y <= rect.top())
		return true;

	// 判断是否与右边相交
	y = k * rect.right() + b;
	if(rect.bottom() <= y && y <= rect.top())
		return true;

	// TODO: 判断是否与上边相交
	// TODO: 判断是否与下边相交
	
	return false;
}

bool collision(CircleCollider c, Line2 l)
{
	const auto center        = c.getPosition();
	const auto startToCenter = center - l.start;
	const auto startToEnd    = l.end - l.start;
	const auto angle         = std::abs(startToCenter.angle() - startToEnd.angle());
	return sin(angle) * startToCenter.size() <= c.getRadius();

	/*const auto center        = c.getPosition();
	const auto startToCenter = center - l.start;
	const auto startToEnd    = l.end - l.start;

	const auto t = startToCenter.dot(startToEnd) / startToEnd.dot(startToEnd);

	if(t < 0.0f || t > 1.0f)
		return false;

	const auto closestPoint = l.start + startToEnd * t;

	collision(c, closestPoint);*/
}
