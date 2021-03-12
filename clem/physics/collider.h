// Copyright 2020 SMS
// License(Apache-2.0)
// 碰撞体

#ifndef CLEM_COLLIDER_H_
#define CLEM_COLLIDER_H_

#include "clem/type/point.h"

class Rigidbody;
class CircleCollider;

/// 碰撞体
class Collider
{
public:
	Collider();
	virtual ~Collider();

	Point getPosition() const;

	void  setOffset(Point);
	Point getOffset() const;

	void       setOwner(Rigidbody*);
	Rigidbody* getOwner() const;

	static bool collides(const CircleCollider&, const CircleCollider&);

protected:
	Point offset;

private:
	Rigidbody* owner;
};

#endif // !CLEM_COLLIDER_H_
