// Copyright 2023 ShenMian
// License(Apache-2.0)

#pragma once

#include "core/time.hpp"
#include "ecs/manager.hpp"
#include "ecs/view.hpp"
#include "rigidbody_component.hpp"

namespace phys
{

class PhysicsSystem
{
public:
	void update(core::Time dt, ecs::Manager& mgr)
	{
		for(auto [body] : ecs::View<Rigidbody>(mgr.get_group<Rigidbody>(), mgr))
		{
		}
	}
};

} // namespace phys
