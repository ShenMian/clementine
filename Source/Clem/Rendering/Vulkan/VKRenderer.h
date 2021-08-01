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

class VKRenderer : public Renderer
{
public:
	void init() override;
	void deinit() override;

private:
	void initInstance();
	void deinitInstance();
	void initDevice();
	void deinitDevice();
};

/**
 * end of Rendering group
 * @}
 */

} // namespace clem