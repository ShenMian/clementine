// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <cstddef>
#include <memory>

namespace clem
{

/**
 * @addtogroup Rendering
 * @{
 */

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

    virtual void   bind()  = 0;
    virtual size_t count() = 0;
};

/**
 * end of Rendering group
 * @}
 */

} // namespace clem