// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Rendering/VertexBuffer.h"

namespace clem
{

class GLVertexBuffer : public VertexBuffer
{
public:
    using handle_type = unsigned int;

    /**
	 * @brief 构造函数.
	 *
	 * @param data 缓冲区.
	 */
    GLVertexBuffer(const std::vector<value_type>& buffer, Usage usage);

    /**
	 * @brief 构造函数.
	 *
	 * @param data 缓冲区数据指针.
	 * @param size 缓冲区数据大小.
	 */
    GLVertexBuffer(const void* data, size_t size, Usage usage);

    /**
	 * @brief 默认析构函数.
	 */
    ~GLVertexBuffer();

    void bind() override;

private:
    handle_type handle;
};

} // namespace clem