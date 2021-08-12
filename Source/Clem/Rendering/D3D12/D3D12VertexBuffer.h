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
	 * @brief ���캯��.
	 *
	 * @param data ������.
	 */
    D3D12VertexBuffer(const std::vector<value_type>& buffer);

    /**
	 * @brief ���캯��.
	 *
	 * @param data ����������ָ��.
	 * @param size ���������ݴ�С.
	 */
    D3D12VertexBuffer(const void* data, size_t size);

    /**
	 * @brief Ĭ����������.
	 */
    ~D3D12VertexBuffer();

private:
};

} // namespace clem