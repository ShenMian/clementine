// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Rendering/VertexBuffer.h"
#include <vulkan/vulkan.hpp>

namespace clem
{

class VKVertexBuffer : public VertexBuffer
{
public:
    using handle_type = vk::Buffer;

    /**
	 * @brief 构造函数.
	 *
	 * @param data 缓冲区.
	 */
    VKVertexBuffer(const std::vector<value_type>& buffer);

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
    handle_type      buffer;
    vk::DeviceMemory memory;
};

} // namespace clem