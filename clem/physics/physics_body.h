
#include "physics_shape.h"

class PhysicsBody
{
public:
	void addShape(PhysicsShape*);
	void removeShape(PhysicsShape*);
	void removeAllShapes();

private:
	std::vector<PhysicsShape*> shapes;
};

