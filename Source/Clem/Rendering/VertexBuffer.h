// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <cstddef>
#include <memory>

namespace clem
{

class VertexBuffer
{
public:
	static std::shared_ptr<VertexBuffer> create(const void* data, size_t size);

	virtual void bind() = 0;
};

} // namespace clem