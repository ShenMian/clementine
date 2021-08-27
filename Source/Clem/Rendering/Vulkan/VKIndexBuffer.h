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
	 * @brief ���캯��.
	 *
	 * @param data ������.
	 */
    VKIndexBuffer(const std::vector<value_type>& buffer, Usage usage);

    /**
	 * @brief ���캯��.
	 *
	 * @param data ����������ָ��.
	 * @param size ���������ݴ�С.
	 */
    VKIndexBuffer(const void* data, size_t size, Usage usage);

    /**
	 * @brief Ĭ����������.
	 */
    ~VKIndexBuffer();

    void bind() override;

private:
    handle_type      buffer;
    vk::DeviceMemory memory;
};

} // namespace clem