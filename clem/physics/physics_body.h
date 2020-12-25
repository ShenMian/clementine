// Copyright 2020 SMS
// License(Apache-2.0)
// 

#include <vector>
#include "type.h"
#include "physics_shape.h"

class PhysicsBody
{
public:
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
	Vec2 velocity
	Vec2 accelerate;

	std::vector<PhysicsShape*> shapes;
};

