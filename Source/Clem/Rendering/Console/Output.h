// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Core/Math/Vector2i.h"
#include "Framebuffer.h"

namespace clem
{
class Output
{
public:
    static Output& get();

    void update();

    /**
	 * @brief 交换缓冲区.
	 */
    void swapBuffers();

    /**
	 * @brief 获取下一个缓冲区.
	 */
    Framebuffer& getBuffer() const;

    /**
	 * @brief 设置缓冲区大小.
	 */
    void setSize(const Size2i&);

    /**
	 * @brief 获取缓冲区大小.
	 */
    const Size2i& getSize();

private:
    Output();

    Framebuffer* front;
    Framebuffer* back;
    Framebuffer  buffer[2];
};
} // namespace clem
