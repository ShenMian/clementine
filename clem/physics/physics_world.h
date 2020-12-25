// Copyright 2020 SMS
// License(Apache-2.0)
//

#include <vector>
#include "physics_body.h"

class PhysicsWorld
{
public:
	void addBody(PhysicsBody*);
	void removeBody(PhysicsBody*);
	void removeAllBodies();	

private:
	std::vector<PhysicsBody*> bodies;
};

