// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <vulkan/vulkan.hpp>

namespace clem
{

class VKPipeline
{
public:
    using handle_type = vk::Pipeline;

    void create();
    void destroy();

private:
    handle_type handle;
};

} // namespace clem