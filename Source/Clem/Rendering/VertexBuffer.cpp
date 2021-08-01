// Copyright 2021 SMS
// License(Apache-2.0)

#include "VertexBuffer.h"
#include "OpenGL/GLVertexBuffer.h"
#include "Renderer.h"

namespace clem
{

std::shared_ptr<VertexBuffer> VertexBuffer::create(const void* data, size_t size)
{
	switch(Renderer::getAPI())
	{
		using enum Renderer::API;
	case OpenGL:
		return std::make_shared<GLVertexBuffer>(data, size);
	}
	return nullptr;
}

} // namespace clem