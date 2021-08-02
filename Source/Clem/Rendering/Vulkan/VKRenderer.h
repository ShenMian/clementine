// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Clem/Rendering/Renderer.h"
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
	void init() override;
	void deinit() override;

private:
    void initInstance();
    void deinitInstance();

    void initDebug();
    void deinitDebug();

    void initDevice();
    void deinitDevice();

	vk::PhysicalDevice findSuitablePhysicalDevice() const;
	bool               isSuitable(const vk::PhysicalDevice& device) const;
	bool               isSuitable(const vk::QueueFamilyProperties& props) const;

    vk::Instance              vkInstance;
    vk::Device                vkDevice;
    std::vector<const char*>  instanceLayers;
    std::vector<const char*>  instanceExtensions;
    std::vector<const char*>  deviceLayers;
    std::vector<const char*>  deviceExtensions;
    vk::DispatchLoaderDynamic dynamicLoader;
};

/**
 * end of Rendering group
 * @}
 */

} // namespace clem