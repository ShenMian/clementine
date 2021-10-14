// Copyright 2021 SMS
// License(Apache-2.0)

#include "Renderer.h"

namespace clem
{

Renderer_::API Renderer_::api = Renderer_::API::OpenGL;

void Renderer_::setAPI(API newAPI)
{
    api = newAPI;
}

Renderer_::API Renderer_::getAPI()
{
    return api;
}

} // namespace clem