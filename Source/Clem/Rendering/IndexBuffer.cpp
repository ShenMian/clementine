// Copyright 2021 SMS
// License(Apache-2.0)

#include "IndexBuffer.h"
#include "OpenGL/GLIndexBuffer.h"

namespace clem
{

std::shared_ptr<IndexBuffer> IndexBuffer::create(const void* data, size_t size)
{
	return std::make_shared<GLIndexBuffer>(data, size);
}

} // namespace clem