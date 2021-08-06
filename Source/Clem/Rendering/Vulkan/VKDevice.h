// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <vulkan/vulkan.hpp>

namespace clem
{

class VKDevice
{
public:
    using handle_type = vk::Device;

    void create();
    void destroy();

    void createBuffer(
        vk::Buffer&             buffer,
        vk::DeviceMemory&       memory,
        vk::DeviceSize          size,
        vk::BufferUsageFlags    usage,
        vk::MemoryPropertyFlags properties);
    void destroyBuffer(vk::Buffer& buffer);

    uint32_t queueFamilyIndex;

    handle_type& operator()();

private:
    vk::PhysicalDevice findSuitablePhysicalDevice() const;
    bool               isSuitable(const vk::PhysicalDevice& device) const;
    bool               isSuitable(const vk::QueueFamilyProperties& props) const;

    handle_type              device;
    vk::Queue                queue;
    vk::PhysicalDevice       physicalDevice;
    std::vector<const char*> deviceLayers;
    std::vector<const char*> deviceExtensions;
};

} // namespace clem