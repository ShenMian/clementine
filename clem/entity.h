// Copyright 2020 SMS
// License(Apache-2.0)
// ΚµΜε

#ifndef CLEM_ENTITY_H_
#define CLEM_ENTITY_H_

#include "factor.h"

class Physics;

class Entity : public Factor
{
	friend class Physics;

public:
	void        setVelocity(const Vec2& v);
	const Vec2& getVelocity() const;
	void        setAccelerate(const Vec2& a);
	const Vec2& getAccelerate() const;
	void        setPhysicsBody(const Rect&);
	const Rect& getPhysicsBody();

private:
	Vec2 velocity;
	Vec2 accelerate;
	Rect physicsBody;
};

#endif // CLEM_ENTITY_H_
