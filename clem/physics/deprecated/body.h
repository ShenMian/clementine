// Copyright 2021 SMS
// License(Apache-2.0)
// ����

#ifndef CLEM_PHYSICS_PHYSICS_BODY_H_
#define CLEM_PHYSICS_PHYSICS_BODY_H_

#include <vector>
#include "type.h"
#include "shape.h"

/// (已弃用)
class PhysicsBody
{
public:
	enum class Type;

	void        setVelocity(const Vec2& v);
	const Vec2& getVelocity() const;
	void        setAccelerate(const Vec2& a);
	const Vec2& getAccelerate() const;
	void        setPhysicsBody(const Rect&);
	const Rect& getPhysicsBody();

	void addShape(PhysicsShape*);
	void removeShape(PhysicsShape*);
	void removeAllShapes();

private:
	Vec2 velocity;
	Vec2 accelerate;

	std::vector<PhysicsShape*> shapes;
};

enum class PhysicsBody::Type
{
	dynamic,
	kinematic,
	STATIC
};

#endif // CLEM_PHYSICS_PHYSICS_BODY_H_
