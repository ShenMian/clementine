// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "VKCommandBuffer.h"
#include "Core/Assert.hpp"
#include "VKRenderer.h"
#include <vulkan/vulkan.hpp>

namespace clem
{

VKCommandBuffer::VKCommandBuffer(const vk::CommandBuffer& handle)
    : handle(handle)
{
}

void VKCommandBuffer::begin()
{
    vk::CommandBufferBeginInfo beginInfo;
    handle.begin(beginInfo);
}

void VKCommandBuffer::end()
{
    handle.end();
}

void VKCommandBuffer::setViewport(int x, int y, int w, int h)
{
    vk::Viewport viewport((float)x, (float)y, (float)w, (float)h);
    handle.setViewport(0, viewport);
}

VKCommandBuffer::operator vk::CommandBuffer()
{
    return handle;
}

vk::CommandBuffer& VKCommandBuffer::operator()()
{
    return handle;
}

} // namespace clem