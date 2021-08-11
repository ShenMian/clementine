// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Rendering/IndexBuffer.h"
#include <vulkan/vulkan.hpp>

namespace clem
{

class VKIndexBuffer : public IndexBuffer
{
public:
    using handle_type = vk::Buffer;

    /**
	 * @brief 构造函数.
	 *
	 * @param data 缓冲区.
	 */
    VKIndexBuffer(const std::vector<value_type>& buffer);

    /**
	 * @brief 构造函数.
	 *
	 * @param data 缓冲区数据指针.
	 * @param size 缓冲区数据大小.
	 */
    VKIndexBuffer(const void* data, size_t size);

    /**
	 * @brief 默认析构函数.
	 */
    ~VKIndexBuffer();

    void bind() override;

private:
    handle_type      buffer;
    vk::DeviceMemory memory;
};

} // namespace clem