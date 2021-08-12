// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Rendering/VertexBuffer.h"
#include <d3d12.h>

namespace clem
{

class D3D12VertexBuffer : public VertexBuffer
{
public:
    /**
	 * @brief 构造函数.
	 *
	 * @param data 缓冲区.
	 */
    D3D12VertexBuffer(const std::vector<value_type>& buffer);

    /**
	 * @brief 构造函数.
	 *
	 * @param data 缓冲区数据指针.
	 * @param size 缓冲区数据大小.
	 */
    D3D12VertexBuffer(const void* data, size_t size);

    /**
	 * @brief 默认析构函数.
	 */
    ~D3D12VertexBuffer();

private:
};

} // namespace clem