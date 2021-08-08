// Copyright 2021 SMS
// License(Apache-2.0)

#include "VKDevice.h"
#include "Assert.hpp"
#include "Logger.h"
#include "VKRenderer.h"

namespace clem
{

void VKDevice::create()
{
    Assert::isTrue(!device);

    physicalDevice = findSuitablePhysicalDevice();
    Assert::isTrue(physicalDevice, "can't find suitable physical device");
    CLEM_LOG_INFO("render", "physical device: {}", physicalDevice.getProperties().deviceName);

    auto     queueFamilyProps = physicalDevice.getQueueFamilyProperties();
    uint32_t queueIndex       = -1;
    for(uint32_t i = 0; i < queueFamilyProps.size(); i++)
        if(isSuitable(queueFamilyProps[i]))
            queueIndex = i;
    Assert::isTrue(queueIndex != -1, "can't find suitable queue family");
    queueFamilyIndex = queueIndex;

    float                     queuePriorities = 1.0f;
    vk::DeviceQueueCreateInfo deviceQueueCreateInfo;
    deviceQueueCreateInfo.queueFamilyIndex = queueFamilyIndex;
    deviceQueueCreateInfo.queueCount       = queueFamilyProps[queueFamilyIndex].queueCount;
    deviceQueueCreateInfo.pQueuePriorities = &queuePriorities;

    vk::DeviceCreateInfo deviceCreateInfo;
    deviceCreateInfo.queueCreateInfoCount    = 1;
    deviceCreateInfo.pQueueCreateInfos       = &deviceQueueCreateInfo;
    deviceCreateInfo.enabledLayerCount       = (uint32_t)deviceLayers.size();
    deviceCreateInfo.ppEnabledLayerNames     = deviceLayers.data();
    deviceCreateInfo.enabledExtensionCount   = (uint32_t)deviceExtensions.size();
    deviceCreateInfo.ppEnabledExtensionNames = deviceExtensions.data();

    try
    {
        device = physicalDevice.createDevice(deviceCreateInfo);
    }
    catch(const std::exception& e)
    {
        Assert::isTrue(false, std::format("create device faild: {}", e.what()));
    }

    queue = device.getQueue(queueFamilyIndex, 0);

    /*
	for(auto& layer : vk::enumerateInstanceLayerProperties())
		std::cout << std::format("{:40} {}", layer.layerName, layer.description) << std::endl;
	std::cout << std::endl;
	for(auto& layer : physicalDevice.enumerateDeviceLayerProperties())
		std::cout << std::format("{:40} {}", layer.layerName, layer.description) << std::endl;
	*/
}

void VKDevice::destroy()
{
    Assert::isTrue(device);

    device.destroy();
    Assert::isTrue(!device);
}

void VKDevice::createBuffer(vk::Buffer& buffer, vk::DeviceMemory& memory, vk::DeviceSize size, vk::BufferUsageFlags usage, vk::MemoryPropertyFlags properties)
{
    vk::BufferCreateInfo bufferInfo;
    bufferInfo.size        = 0;
    bufferInfo.usage       = usage;
    bufferInfo.sharingMode = vk::SharingMode::eExclusive;

    try
    {
        buffer = device.createBuffer(bufferInfo);
    }
    catch(const std::exception& e)
    {
        Assert::isTrue(false, std::format("create buffer faild: {}", e.what()));
    }

    auto memRequirements = device.getBufferMemoryRequirements(buffer);

    vk::MemoryAllocateInfo allocInfo;
    allocInfo.allocationSize = memRequirements.size;

    device.bindBufferMemory(buffer, memory, 0);
}

void VKDevice::destroyBuffer(vk::Buffer& buffer)
{
    device.destroyBuffer(buffer);
}

vk::Device& VKDevice::operator()()
{
    return device;
}

vk::PhysicalDevice VKDevice::findSuitablePhysicalDevice() const
{
    for(const auto device : VKRenderer::get().instance.enumeratePhysicalDevices())
        if(isSuitable(device))
            return device;
    return nullptr;
}

bool VKDevice::isSuitable(const vk::PhysicalDevice& device) const
{
    // 检查是否为独立显卡
    if(device.getProperties().deviceType != vk::PhysicalDeviceType::eDiscreteGpu)
        return false;
    return true;
}

bool VKDevice::isSuitable(const vk::QueueFamilyProperties& props) const
{
    return props.queueFlags & vk::QueueFlagBits::eGraphics && props.queueCount > 0;
}

} // namespace clem