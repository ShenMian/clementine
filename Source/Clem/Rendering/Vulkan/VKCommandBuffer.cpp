// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "VKCommandBuffer.h"
#include "Assert.h"
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

VKCommandBuffer::operator vk::CommandBuffer()
{
  return handle;
}

} // namespace clem