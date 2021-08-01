// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <memory>

namespace clem
{

/**
 * @addtogroup Rendering
 * @{
 */

class Renderer
{
public:
	enum class API
	{
		OpenGL,
		Vulkan,
		Direct3D,
		Metal
	};

	static Renderer* get();

	void setApi(API api);
	API  getApi();

	virtual void init() = 0;
	virtual void deinit() = 0;

private:
	API api;

	static Renderer* instance;
};

/**
 * end of Rendering group
 * @}
 */

} // namespace clem