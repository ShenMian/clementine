﻿// Copyright 2021 ShenMian
// License(Apache-2.0)

#pragma once

#include "BoxCollider.h"
#include "SphereCollider.h"

namespace phys
{

namespace algo
{

inline bool intersects(const BoxCollider& box, const SphereCollider& sphere)
{
	return false;
}

inline bool intersects(const SphereCollider& sphere, const BoxCollider& box)
{
	return intersects(box, sphere);
}

}

}