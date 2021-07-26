// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Clem/Rendering/VertexBuffer.h"

namespace clem
{

class OpenGLVertexBuffer : public VertexBuffer
{
public:
	OpenGLVertexBuffer(const void* data, size_t size);
	~OpenGLVertexBuffer();

	void bind() override;

private:
	unsigned int buffer;
};

} // namespace clem