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
	void          setVelocity(const Vector& v);
	const Vector& getVelocity() const;
	void          setAccelerate(const Vector& a);
	const Vector& getAccelerate() const;

	void        setHitbox(const Rect& hitbox);
	const Rect& getHitbox() const;

private:
	Vector velocity;
	Vector accelerate;
	Rect   hitbox;
};

#endif // CLEM_ENTITY_H_
