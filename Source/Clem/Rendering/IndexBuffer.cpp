// Copyright 2021 SMS
// License(Apache-2.0)

#include "IndexBuffer.h"
#include "OpenGL/GLIndexBuffer.h"
#include "Renderer.h"
#include "Vulkan/VKIndexBuffer.h"

namespace clem
{

std::shared_ptr<IndexBuffer> IndexBuffer::create(const std::vector<value_type>& data)
{
    switch(Renderer::getAPI())
    {
        using enum Renderer::API;

    case OpenGL:
        return std::make_shared<GLIndexBuffer>(data);

    case Vulkan:
        return std::make_shared<VKIndexBuffer>(data);
    }
    return nullptr;
}

std::shared_ptr<IndexBuffer> IndexBuffer::create(const void* data, size_t size)
{
    switch(Renderer::getAPI())
    {
        using enum Renderer::API;

    case OpenGL:
        return std::make_shared<GLIndexBuffer>(data, size);

    case Vulkan:
        return std::make_shared<VKIndexBuffer>(data, size);
    }
    return nullptr;
}

size_t IndexBuffer::size() const
{
    return size_;
}

size_t IndexBuffer::count() const
{
    return count_;
}

} // namespace clem