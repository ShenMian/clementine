// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Clem/Rendering/VertexBuffer.h"

namespace clem
{

class OpenGLVertexBuffer : public VertexBuffer
{
public:
	using id_type = unsigned int;

	OpenGLVertexBuffer(const void* data, size_t size);
	~OpenGLVertexBuffer();

	void bind() override;

private:
	id_type buffer;
};

} // namespace clem