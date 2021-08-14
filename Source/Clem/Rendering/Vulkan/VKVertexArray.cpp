// Copyright 2021 SMS
// License(Apache-2.0)

#include "VKVertexArray.h"

namespace clem
{

static std::unordered_map<Shader::Type, vk::Format> VKType = {
    {Shader::Type::Float, vk::Format::eR32Sfloat},
    {Shader::Type::Float2, vk::Format::eR32G32Sfloat},
    {Shader::Type::Float3, vk::Format::eR32G32B32Sfloat},
    {Shader::Type::Float4, vk::Format::eR32G32B32A32Sfloat},
    {Shader::Type::Mat3, vk::Format::eR32G32B32Sfloat},
    {Shader::Type::Mat4, vk::Format::eR32G32B32A32Sfloat},
    {Shader::Type::Int, vk::Format::eR32Sint},
    {Shader::Type::Int2, vk::Format::eR32G32Sint},
    {Shader::Type::Int3, vk::Format::eR32G32B32Sint},
    {Shader::Type::Int4, vk::Format::eR32G32B32A32Sint}};

} // namespace clem