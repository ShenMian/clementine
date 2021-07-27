// Copyright 2021 SMS
// License(Apache-2.0)

#include "VertexBuffer.h"
#include "OpenGL/OpenGLVertexBuffer.h"

namespace clem
{

std::shared_ptr<VertexBuffer> VertexBuffer::create(const void* data, size_t size)
{
	return std::make_shared<OpenGLVertexBuffer>(data, size);
}

} // namespace clem