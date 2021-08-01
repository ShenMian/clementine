// Copyright 2021 SMS
// License(Apache-2.0)

#include "IndexBuffer.h"
#include "OpenGL/GLIndexBuffer.h"
#include "Renderer.h"

namespace clem
{

std::shared_ptr<IndexBuffer> IndexBuffer::create(const void* data, size_t size)
{
	switch(Renderer::getAPI())
	{
		using enum Renderer::API;
	case OpenGL:
		return std::make_shared<GLIndexBuffer>(data, size);
	}
	return nullptr;
}

} // namespace clem