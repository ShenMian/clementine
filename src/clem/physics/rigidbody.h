// Copyright 2021 SMS
// License(Apache-2.0)

#ifndef CLEM_PHYSICS_RIGIDBODY_H_
#define CLEM_PHYSICS_RIGIDBODY_H_

#include <vector>
#include "clem/math/vec2.h"
#include "clem/component.h"

class Collider;

/**
 * @addtogroup physics
 * @{
 */

/**
 * 刚体.
 */
class Rigidbody : public Component
{
public:
	Vec2 velocity;
	Vec2 accelerate;

	void update(float dt) override;

	void                          addCollider(Collider&);
	const std::vector<Collider*>& getColliders() const;

	void onAdd() override;
	void onRemove() override;

private:
	std::vector<Collider*> colliders;
};

/**
 * end of physics group
 * @}
 */

#endif // !CLEM_PHYSICS_RIGIDBODY_H_
