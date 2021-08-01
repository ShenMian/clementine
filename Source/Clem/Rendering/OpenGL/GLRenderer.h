// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Clem/Rendering/Renderer.h"

namespace clem
{

/**
 * @addtogroup Rendering
 * @{
 */

class GLRenderer : public Renderer
{
public:
	void init() override;
	void deinit() override;
};

/**
 * end of Rendering group
 * @}
 */

} // namespace clem