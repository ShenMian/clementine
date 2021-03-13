// Copyright 2020 SMS
// License(Apache-2.0)
// 碰撞体

#ifndef CLEM_COLLIDER_H_
#define CLEM_COLLIDER_H_

#include "clem/type/point.h"

class Rigidbody;
class BoxCollider;
class CircleCollider;

/// 碰撞体
class Collider
{
public:
	Collider();
	virtual ~Collider();

	virtual bool collides(const Collider& other) const = 0;

	Point getPosition() const;

	void  setOffset(Point);
	Point getOffset() const;

	void       setOwner(Rigidbody*);
	Rigidbody* getOwner() const;

protected:
	Point offset;

private:
	Rigidbody* owner;
};

#endif // !CLEM_COLLIDER_H_
