// Copyright 2021 SMS
// License(Apache-2.0)

#include "VKIndexBuffer.h"
#include "Assert.hpp"
#include "VKRenderer.h"

namespace clem
{

VKIndexBuffer::VKIndexBuffer(const std::vector<value_type>& buf, Usage usage)
    : VKIndexBuffer(buf.data(), buf.size() * sizeof(value_type), usage)
{
}

VKIndexBuffer::VKIndexBuffer(const void* data, size_t size, Usage usage)
{
    size_  = size;
    count_ = size / sizeof(value_type);

    auto& device = VKRenderer::get().device;

    device.createBuffer(buffer, memory, size, vk::BufferUsageFlagBits::eIndexBuffer,
                        vk::MemoryPropertyFlagBits::eHostCoherent | vk::MemoryPropertyFlagBits::eHostVisible);

    void* bufferData;
    auto  ret = device().mapMemory(memory, 0, static_cast<vk::DeviceSize>(size), {}, &bufferData);
    Assert::isTrue(ret == vk::Result::eSuccess);
    std::memcpy(bufferData, data, size);
    device().unmapMemory(memory);
}

VKIndexBuffer::~VKIndexBuffer()
{
    VKRenderer::get().device.destroyBuffer(buffer);
}

void VKIndexBuffer::bind()
{
}

} // namespace clem