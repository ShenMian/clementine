// Copyright 2021 SMS
// License(Apache-2.0)

#include "D3D12VertexBuffer.h"
#include "Assert.hpp"
#include <dxgi.h>

namespace clem
{

D3D12VertexBuffer::D3D12VertexBuffer(const std::vector<value_type>& buf)
    : D3D12VertexBuffer(buf.data(), buf.size() * sizeof(value_type))
{
}

D3D12VertexBuffer::D3D12VertexBuffer(const void* data, size_t size)
{
    D3D12_RESOURCE_DESC desc = {};
    desc.Dimension           = D3D12_RESOURCE_DIMENSION_BUFFER;
}

} // namespace clem