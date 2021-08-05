// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "VKCommandPool.h"
#include "Assert.hpp"
#include "VKCommandBuffer.h"
#include "VKRenderer.h"
#include <vector>
#include <vulkan/vulkan.hpp>

namespace clem
{

void VKCommandPool::create()
{
    vk::CommandPoolCreateInfo createInfo;
    createInfo.flags            = vk::CommandPoolCreateFlagBits::eResetCommandBuffer;
    createInfo.queueFamilyIndex = VKRenderer::get().device.queueFamilyIndex;

    try
    {
        handle = VKRenderer::get().device.handle().createCommandPool(createInfo);
    }
    catch(const std::exception& e)
    {
        Assert::isTrue(false, std::format("create command pool faild: {}", e.what()));
    }
}

void VKCommandPool::destroy()
{
    VKRenderer::get().device.handle().destroyCommandPool(handle);
}

VKCommandBuffer VKCommandPool::allocateCommandBuffer()
{
    vk::CommandBufferAllocateInfo allocateInfo;
    allocateInfo.commandBufferCount = 1;
    allocateInfo.commandPool        = handle;
    allocateInfo.level              = vk::CommandBufferLevel::ePrimary;

    std::vector<vk::CommandBuffer> buffers;

    try
    {
        buffers = VKRenderer::get().device.handle().allocateCommandBuffers(allocateInfo);
    }
    catch(const std::exception& e)
    {
        Assert::isTrue(false, std::format("allocate command buffers faild: {}", e.what()));
    }

    return VKCommandBuffer(buffers[0]);
}

VKCommandPool::operator vk::CommandPool()
{
    return handle;
}

} // namespace clem