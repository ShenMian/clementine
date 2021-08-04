// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Rendering/Renderer.h"
#include "VKDevice.h"
#include "VKCommandBuffer.h"
#include "VKCommandPool.h"
#include <tuple>
#include <vector>
#include <vulkan/vulkan.hpp>

namespace clem
{

/**
 * @addtogroup Rendering
 * @{
 */

class VKRenderer : public Renderer
{
public:
    static VKRenderer& get();

    void init() override;
    void deinit() override;

    vk::Instance instance;
    VKDevice     device;

private:
    VKRenderer() = default;

    void createInstance();
    void destroyInstance();

    void createDebugCallback();
    void destroyDebugCallback();

    std::vector<const char*>  instanceLayers;
    std::vector<const char*>  instanceExtensions;
    vk::DispatchLoaderDynamic dynamicLoader;

    VKCommandPool   commandPool;
    VKCommandBuffer commandBuffer;
};

/**
 * end of Rendering group
 * @}
 */

} // namespace clem