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
		DirectX12,
		Metal
	};

	static Renderer* get();

	static void setAPI(API api);
	static API  getAPI();

	virtual void init()   = 0;
	virtual void deinit() = 0;

private:
	static API       api;
	static Renderer* instance;
};

/**
 * end of Rendering group
 * @}
 */

} // namespace clem