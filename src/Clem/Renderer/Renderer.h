// Copyright 2021 SMS
// License(Apache-2.0)

#ifndef CLEM_RENDERER_RENDERER_H_
#define CLEM_RENDERER_RENDERER_H_

#include "Clem/Core/Math/Vector2i.h"
#include "Framebuffer.h"

class Renderer
{
public:
	static Renderer& getInstance();

	void output();

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
	Renderer();

	Framebuffer* front;
	Framebuffer* back;
	Framebuffer  buffer[2];
};

#endif // !CLEM_RENDERER_RENDERER_H_
