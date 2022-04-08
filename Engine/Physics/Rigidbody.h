// Copyright 2021 ShenMian
// License(Apache-2.0)

#pragma once

namespace phys
{

class Rigidbody
{
	float mass = 0.f;
};

struct Material
{
	float staticFriction;
	float dynamicFriction;
	float restitution;
};

}
