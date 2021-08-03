// Copyright 2021 SMS
// License(Apache-2.0)

#include "Renderer.h"
#include "OpenGL/GLRenderer.h"
#include "Vulkan/VKRenderer.h"
#include <cassert>

namespace clem
{

Renderer::API Renderer::api       = Renderer::API::OpenGL;
Renderer*     Renderer::instance_ = nullptr;

Renderer* Renderer::get()
{
    static API currentAPI;
    if(instance_ == nullptr || currentAPI != api)
    {
        delete instance_;
        switch(api)
        {
        case API::OpenGL:
            instance_ = &GLRenderer::get();
            break;

        case API::Vulkan:
            instance_ = &VKRenderer::get();
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

    return instance_;
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