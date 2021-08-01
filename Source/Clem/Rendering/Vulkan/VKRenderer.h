// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Clem/Rendering/Renderer.h"
#include <tuple>
#include <vulkan/vulkan.h>

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
	void initDevice();
	void deinitDevice();

	VkPhysicalDevice findSuitableDevice() const;
	bool             isDeviceSuitable(const VkPhysicalDevice device) const;

	std::tuple<uint32_t, uint32_t> findSuitableQueueFamily(const VkPhysicalDevice device) const;
	bool                           isQueueFamilySuitable(VkQueueFamilyProperties&) const;
};

/**
 * end of Rendering group
 * @}
 */

} // namespace clem