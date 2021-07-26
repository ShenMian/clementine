// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Clem/Components/Transform.h"
#include "Output.h"

namespace clem
{

/**
 * @addtogroup Physics
 * @{
 */

class RenderSystem : public System
{
public:
	void update(Time dt, Registry& registry)
	{
		static auto& output = Output::get();
		output.getBuffer().clear();

		registry.each<Sprite>([](const Entity& e, Sprite& sprite) {
			auto& tf = e.get<Transform>();
			output.getBuffer().drawSprite(tf.getWorldPosition(), sprite);
		});

		output.swapBuffers();
		output.update();
	}
};

/**
 * end of Physics group
 * @}
 */

} // namespace clem
