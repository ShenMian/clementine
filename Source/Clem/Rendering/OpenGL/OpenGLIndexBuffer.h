// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Clem/Rendering/IndexBuffer.h"

namespace clem
{

class OpenGLIndexBuffer : public IndexBuffer
{
public:
	OpenGLIndexBuffer(const void* data, size_t size);
	~OpenGLIndexBuffer();

	void bind() override;

private:
	unsigned int buffer;
};

} // namespace clem