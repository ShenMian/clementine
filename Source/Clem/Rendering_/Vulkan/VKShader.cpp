// Copyright 2021 SMS
// License(Apache-2.0)

#include "VKShader.h"
#include <vulkan/vulkan.h>

namespace clem
{

VKShader_::VKShader_(const std::string& name, Stage stage)
    : Shader_(name, stage)
{
}

size_t VKShader_::getNativeHandle() const
{
    // TODO
    return size_t();
}

} // namespace clem