// Copyright 2021 SMS
// License(Apache-2.0)

#include "Renderer.h"
#include "OpenGL/GLRenderer.h"
#include "Vulkan/VKRenderer.h"
#include <cassert>

namespace clem
{

Renderer* Renderer::instance = nullptr;

Renderer* Renderer::get()
{
	assert(instance != nullptr);
	return instance;
}

void Renderer::setApi(API api)
{
	this->api = api;
	instance->deinit();
	delete instance;
	switch(api)
	{
	case API::OpenGL:
		instance = new GLRenderer;
		break;

	case API::Vulkan:
		instance = new VKRenderer;
		break;

	default:
		assert(false);
	}
	instance->init();
}

Renderer::API Renderer::getApi()
{
	return api;
}

} // namespace clem