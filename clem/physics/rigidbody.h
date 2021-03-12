// Copyright 2020 SMS
// License(Apache-2.0)
// ∏’ÃÂ

#ifndef CLEM_PHYSICS_RIGIDBODY_H_
#define CLEM_PHYSICS_RIGIDBODY_H_

#include <vector>
#include "clem/type/vec2.h"
#include "clem/component.h"

class Collider;

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

#endif // !CLEM_PHYSICS_RIGIDBODY_H_
