// Copyright 2021 SMS
// License(Apache-2.0)

#include "VKVertexBuffer.h"
#include "Assert.hpp"
#include "VKRenderer.h"

namespace clem
{

VKVertexBuffer::VKVertexBuffer(const void* data, size_t size)
{
    auto& device = VKRenderer::get().device;

    // Host: CPU, Device: GPU
    device.createBuffer(buffer, memory, size, vk::BufferUsageFlagBits::eVertexBuffer,
                        vk::MemoryPropertyFlagBits::eHostCoherent | vk::MemoryPropertyFlagBits::eHostVisible);

    void* bufferData;
    auto  ret = device().mapMemory(memory, 0, static_cast<vk::DeviceSize>(size), {}, &bufferData);
    Assert::isTrue(ret == vk::Result::eSuccess);
    std::memcpy(bufferData, data, size);
    device().unmapMemory(memory);
}

VKVertexBuffer::~VKVertexBuffer()
{
    VKRenderer::get().device.destroyBuffer(buffer);
}

void VKVertexBuffer::bind()
{
}

} // namespace clem