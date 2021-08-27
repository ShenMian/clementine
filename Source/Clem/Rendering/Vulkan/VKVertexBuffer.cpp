// Copyright 2021 SMS
// License(Apache-2.0)

#include "VKVertexBuffer.h"
#include "Assert.hpp"
#include "VKRenderer.h"

namespace clem
{

VKVertexBuffer::VKVertexBuffer(const std::vector<value_type>& buf, Usage usage)
    : VKVertexBuffer(buf.data(), buf.size() * sizeof(value_type), usage)
{
}

VKVertexBuffer::VKVertexBuffer(const void* data, size_t size, Usage usage)
{
    size_ = size;

    auto& device = VKRenderer::get().device;

    // Host: CPU, Device: GPU
    device.createBuffer(handle, memory, size, vk::BufferUsageFlagBits::eVertexBuffer,
                        vk::MemoryPropertyFlagBits::eHostCoherent | vk::MemoryPropertyFlagBits::eHostVisible);

    void* bufferData;
    auto  ret = device().mapMemory(memory, 0, static_cast<vk::DeviceSize>(size), {}, &bufferData);
    Assert::isTrue(ret == vk::Result::eSuccess);
    std::memcpy(bufferData, data, size);
    device().unmapMemory(memory);
}

VKVertexBuffer::~VKVertexBuffer()
{
    VKRenderer::get().device.destroyBuffer(handle);
}

void VKVertexBuffer::bind()
{
    vk::DeviceSize offset = 0;
    VKRenderer::get().cmdBuffer().bindVertexBuffers(0, handle, offset);
}

} // namespace clem