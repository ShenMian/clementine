// Copyright 2021 SMS
// License(Apache-2.0)

#include "VertexBuffer.h"
#include "OpenGL/GLVertexBuffer.h"
#include "Renderer.h"
#include "Vulkan/VKVertexBuffer.h"

namespace clem
{

std::shared_ptr<VertexBuffer> VertexBuffer::create(const std::vector<value_type>& data, Usage usage)
{
    switch(Renderer::getAPI())
    {
        using enum Renderer::API;

    case OpenGL:
        return std::make_shared<GLVertexBuffer>(data.data(), data.size() * sizeof(value_type), usage);

    case Vulkan:
        return std::make_shared<VKVertexBuffer>(data.data(), data.size() * sizeof(value_type), usage);
    }
    return nullptr;
}
std::shared_ptr<VertexBuffer> VertexBuffer::create(const void* data, size_t size, Usage usage)
{
    switch(Renderer::getAPI())
    {
        using enum Renderer::API;

    case OpenGL:
        return std::make_shared<GLVertexBuffer>(data, size, usage);

    case Vulkan:
        return std::make_shared<VKVertexBuffer>(data, size, usage);
    }
    return nullptr;
}

size_t VertexBuffer::size() const
{
    return size_;
}

size_t VertexBuffer::count() const
{
    return count_;
}

VertexBuffer::Layout::Layout(const std::initializer_list<Element>& list)
    : elements_(list)
{
    for(auto& e : elements_)
    {
        e.offset = stride_;
        stride_ += e.size();
    }
}

const std::vector<VertexBuffer::Layout::Element>& VertexBuffer::Layout::elements() const
{
    return elements_;
}

size_t VertexBuffer::Layout::stride() const
{
    return stride_;
}

bool VertexBuffer::Layout::empty() const
{
    return elements_.empty();
}

std::vector<VertexBuffer::Layout::Element>::iterator VertexBuffer::Layout::begin()
{
    return elements_.begin();
}

std::vector<VertexBuffer::Layout::Element>::iterator VertexBuffer::Layout::end()
{
    return elements_.end();
}

std::vector<VertexBuffer::Layout::Element>::const_iterator VertexBuffer::Layout::begin() const
{
    return elements_.begin();
}

std::vector<VertexBuffer::Layout::Element>::const_iterator VertexBuffer::Layout::end() const
{
    return elements_.end();
}

VertexBuffer::Layout::Element::Element(const std::string& name, Shader::Type type, bool normalized)
    : name(name), type(type), normalized(normalized)
{
}

size_t VertexBuffer::Layout::Element::count() const
{
    return countOf[type];
}

size_t VertexBuffer::Layout::Element::size() const
{
    return sizeOf[type];
}

std::unordered_map<Shader::Type, size_t> VertexBuffer::Layout::Element::sizeOf = {
    {Shader::Type::Float, 4},
    {Shader::Type::Float2, 4 * 2},
    {Shader::Type::Float3, 4 * 3},
    {Shader::Type::Float4, 4 * 4},
    {Shader::Type::Mat3, 4 * 3 * 3},
    {Shader::Type::Mat4, 4 * 4 * 4},
    {Shader::Type::Int, 4},
    {Shader::Type::Int2, 4 * 2},
    {Shader::Type::Int3, 4 * 3},
    {Shader::Type::Int4, 4 * 4},
    {Shader::Type::Bool, 1}};

std::unordered_map<Shader::Type, size_t> VertexBuffer::Layout::Element::countOf = {
    {Shader::Type::Float, 1},
    {Shader::Type::Float2, 2},
    {Shader::Type::Float3, 3},
    {Shader::Type::Float4, 4},
    {Shader::Type::Mat3, 3},
    {Shader::Type::Mat4, 4},
    {Shader::Type::Int, 1},
    {Shader::Type::Int2, 2},
    {Shader::Type::Int3, 3},
    {Shader::Type::Int4, 4},
    {Shader::Type::Bool, 1}};

} // namespace clem