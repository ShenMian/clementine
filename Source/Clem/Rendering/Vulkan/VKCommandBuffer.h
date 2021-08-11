// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Rendering/Renderer.h"
#include <vulkan/vulkan.hpp>

namespace clem
{

/**
 * @addtogroup Rendering
 * @{
 */

class VKCommandBuffer
{
public:
    VKCommandBuffer() = default;
    VKCommandBuffer(const vk::CommandBuffer&);

    void begin();
    void end();

    operator vk::CommandBuffer();
    vk::CommandBuffer& operator()();

private:
    vk::CommandBuffer handle;
};

/**
* end of Rendering group
* @}
*/

} // namespace clem