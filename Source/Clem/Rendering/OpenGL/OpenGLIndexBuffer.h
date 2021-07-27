// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Clem/Rendering/IndexBuffer.h"

namespace clem
{

class OpenGLIndexBuffer : public IndexBuffer
{
public:
	using id_type = unsigned int;

	/**
	 * @brief 构造函数.
	 * 
	 * @param data 缓冲区数据指针.
	 * @param size 缓冲区数据大小.
	 */
	OpenGLIndexBuffer(const void* data, size_t size);

	/**
	 * @brief 默认析构函数.
	 */
	~OpenGLIndexBuffer();

	void bind() override;

private:
	id_type buffer;
};

} // namespace clem