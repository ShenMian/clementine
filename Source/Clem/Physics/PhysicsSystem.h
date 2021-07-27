// Copyright 2021 SMS
// License(Apache-2.0)

#include "Clem/Components/Transform.h"
#include "Rigidbody.h"

namespace clem
{

/**
 * @addtogroup Physics
 * @{
 */

class PhysicsSystem : public System
{
public:
	void update(Time dt, Registry& registry)
	{
		registry.each<Rigidbody>([&](const Entity& e, Rigidbody& body) {
			auto& tf = e.get<Transform>();
			switch(body.type)
			{
			case Rigidbody::Type::Dynamic:
				body.velocity += (body.getAcceleration() + gravity) * dt.seconds(); // v += (a + g) * dt;
				break;

			case Rigidbody::Type::Kinematic:
				body.velocity += body.getAcceleration() * dt.seconds(); // v += a * dt;
				break;

			case Rigidbody::Type::Static:
				break;
			}
			tf.translation += body.velocity; // p += v * dt;
		});
	}

private:
	const Vector2 gravity = {0.0f, 9.8f};
};

/**
 * end of Physics group
 * @}
 */

} // namespace clem
