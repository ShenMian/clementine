// Copyright 2021 SMS
// License(Apache-2.0)

#include "IndexBuffer.h"
#include "OpenGL/OpenGLIndexBuffer.h"

namespace clem
{

std::shared_ptr<IndexBuffer> IndexBuffer::create(const void* data, size_t size)
{
	return std::make_shared<OpenGLIndexBuffer>(data, size);
}

} // namespace clem
