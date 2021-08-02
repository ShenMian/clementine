// Copyright 2021 SMS
// License(Apache-2.0)

#include "Renderer.h"
#include "OpenGL/GLRenderer.h"
#include "Vulkan/VKRenderer.h"
#include <cassert>

namespace clem
{

Renderer::API Renderer::api      = Renderer::API::OpenGL;
Renderer*     Renderer::instance = nullptr;

Renderer* Renderer::get()
{
	static API currentAPI;
	if(instance == nullptr || currentAPI != api)
	{
		delete instance;
		switch(api)
		{
		case API::OpenGL:
			instance = new GLRenderer;
			break;

		case API::Vulkan:
			instance = new VKRenderer;
			break;

		case API::D3D12:
			assert(false);
			break;

		case API::Metal:
			assert(false);
			break;
		}
		currentAPI = api;
	}

	return instance;
}

void Renderer::setAPI(API newAPI)
{
	api = newAPI;
}

Renderer::API Renderer::getAPI()
{
	return api;
}

} // namespace clem