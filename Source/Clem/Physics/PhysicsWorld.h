// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Clem/Core/Math/Math.h"
#include <vector>

namespace clem
{

class Scene;
class Rigidbody;

/**
 * @addtogroup Physics
 * @{
 */

class PhysicsWorld
{
public:
	PhysicsWorld(Scene&);

	void update(float dt);

	void addBody(Rigidbody&);
	bool removeBody(Rigidbody&);

	void setGravity(const Vector2&);

private:
	std::vector<Rigidbody*> bodies;
	Scene&                  scene;
	Vector2                 gravity;
};

/**
 * end of Physics group
 * @}
 */

} // namespace clem
