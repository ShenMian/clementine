// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Rendering/CommandBuffer.h"
#include <vulkan/vulkan.hpp>

namespace clem
{

/**
 * @addtogroup Rendering
 * @{
 */

class VKCommandBuffer : public CommandBuffer
{
public:
    VKCommandBuffer() = default;
    VKCommandBuffer(const vk::CommandBuffer&);

    void beginFrame() override;
    void endFrame() override;
    void setViewport(int x, int y, int width, int height) override;

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