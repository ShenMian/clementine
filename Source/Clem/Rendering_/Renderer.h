// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

namespace clem
{

/**
 * @addtogroup Rendering
 * @{
 */

class Renderer_
{
public:
    enum class API
    {
        OpenGL,
        Vulkan,
        D3D12,
        Metal
    };

    static API getAPI()
    {
        return API::OpenGL;
    }
};

/**
 * end of Rendering group
 * @}
 */

} // namespace clem