// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <cstddef>
#include <memory>

namespace clem
{

class IndexBuffer
{
public:
	/**
	 * @brief 创建 IndexBuffer.
	 *
	 * @param data 缓冲区数据指针.
	 * @param size 缓冲区数据大小.
	 */
	static std::shared_ptr<IndexBuffer> create(const void* data, size_t size);

	virtual void bind() = 0;
};

} // namespace clem