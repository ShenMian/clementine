// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Rendering/Renderer.h"
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

    vk::Device device;
    uint32_t   queueFamilyIndex;

private:
    VKRenderer() = default;

    void createInstance();
    void destroyInstance();

    void createDebugCallback();
    void destroyDebugCallback();

    void createDevice();
    void destroyDevice();

    vk::PhysicalDevice findSuitablePhysicalDevice() const;
    bool               isSuitable(const vk::PhysicalDevice& device) const;
    bool               isSuitable(const vk::QueueFamilyProperties& props) const;

    vk::Instance              instance;
    vk::Queue                 queue;
    std::vector<const char*>  instanceLayers;
    std::vector<const char*>  instanceExtensions;
    std::vector<const char*>  deviceLayers;
    std::vector<const char*>  deviceExtensions;
    vk::DispatchLoaderDynamic dynamicLoader;

    VKCommandPool   commandPool;
    VKCommandBuffer commandBuffer;
};

/**
 * end of Rendering group
 * @}
 */

} // namespace clem