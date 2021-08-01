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
			// instance = new VKRenderer;
			assert(false);
			break;

		case API::DirectX12:
			assert(false);
			break;

		case API::Metal:
			assert(false);
			break;

		default:
			assert(false);
		}
		currentAPI = api;
	}

	return instance;
}

void Renderer::setApi(API newAPI)
{
	api = newAPI;
}

Renderer::API Renderer::getApi()
{
	return api;
}

} // namespace clem