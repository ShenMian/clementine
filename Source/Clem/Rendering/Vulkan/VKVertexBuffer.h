﻿// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Rendering/VertexBuffer.h"
#include <vulkan/vulkan.hpp>

namespace clem
{

class VKVertexBuffer : public VertexBuffer
{
public:
    using id_type = unsigned int;

    /**
	 * @brief 构造函数.
	 *
	 * @param data 缓冲区数据指针.
	 * @param size 缓冲区数据大小.
	 */
    VKVertexBuffer(const void* data, size_t size);

    /**
	 * @brief 默认析构函数.
	 */
    ~VKVertexBuffer();

    void bind() override;

private:
    vk::Buffer       buffer;
    vk::DeviceMemory memory;
};

} // namespace clem