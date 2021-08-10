// Copyright 2021 SMS
// License(Apache-2.0)

#include "BoxCollider.h"
#include "CircleCollider.h"
#include "Core/Math/Math.h"
#include <cassert>

using namespace clem;

/**
 * @brief 二维线段.
 */
struct Line2
{
    Point2 start;
    Point2 end;
};

bool collision(const Line2& l, const Point2& p)
{
    const auto dx = l.end.x - l.start.x;
    const auto dy = l.end.y - l.start.y;
    assert(dx != 0 && dy != 0);
    const auto k = dy / dx;
    const auto b = l.start.y; // b = l.end.y - k * l.end.x

    return p.y == k * p.x + b;
}

bool collision(const BoxCollider& b, const Point2& p)
{
    return b.getRect().intersectsPoint(p);
}

// TODO: CircleCollider::getCenter();
bool collision(const CircleCollider& c, const Point2& p)
{
    const auto center = c.getPosition();
    return center.distanceSquared(p) <= c.getRadius() * c.getRadius();
}

bool collision(const BoxCollider& a, const BoxCollider& b)
{
    return a.getRect().intersectsRect(b.getRect());
}

bool collision(const CircleCollider& a, const CircleCollider& b)
{
    const auto aCenter = a.getPosition();
    const auto bCenter = b.getPosition();
    return aCenter.distance(bCenter) <= a.getRadius() + b.getRadius();
}

bool collision(const BoxCollider& box, const Line2& l)
{
    const auto rect = box.getRect();

    const auto dx = l.end.x - l.start.x;
    const auto dy = l.end.y - l.start.y;
    assert(dx != 0 && dy != 0);
    const auto k = dy / dx;
    const auto b = l.start.y;

    auto y = k * rect.left() + b;
    if(rect.bottom() <= y && y <= rect.top())
        return true;

    y = k * rect.right() + b;
    if(rect.bottom() <= y && y <= rect.top())
        return true;

    return false;
}

bool collision(const CircleCollider& c, const Line2& l)
{
    const auto center        = c.getPosition();
    const auto startToCenter = center - l.start;
    const auto startToEnd    = l.end - l.start;
    const auto angle         = std::abs(startToCenter.angle() - startToEnd.angle());
    return sin(angle) * startToCenter.size() <= c.getRadius();
}

/*const auto center        = c.getPosition();
	const auto startToCenter = center - l.start;
	const auto startToEnd    = l.end - l.start;

	const auto t = startToCenter.dot(startToEnd) / startToEnd.dot(startToEnd);

	if(t < 0.f || t > 1.f)
		return false;

	const auto closestPoint = l.start + startToEnd * t;

	collision(c, closestPoint);*/

bool collision(BoxCollider b, CircleCollider c)
{
    return false;
}