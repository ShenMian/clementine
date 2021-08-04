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
    device.handle().mapMemory(memory, 0, static_cast<vk::DeviceSize>(size), {}, &bufferData);
    std::memcpy(bufferData, data, size);
    device.handle().unmapMemory(memory);
}

VKVertexBuffer::~VKVertexBuffer()
{
    VKRenderer::get().device.destroyBuffer(buffer);
}

void VKVertexBuffer::bind()
{
    // TODO
}

} // namespace clem