// Copyright 2021 SMS
// License(Apache-2.0)

#ifndef CLEM_RENDERER_RENDERER_H_
#define CLEM_RENDERER_RENDERER_H_

#include "Framebuffer.h"
#include "Clem/Math/Vec2.h"

class Renderer
{
public:
	Renderer();

	void render();

	/**
	 * @brief 交换缓冲区.
	 */
	void swapBuffer();

	/**
	 * @brief 设置缓冲区大小.
	 */
	void setSize(const Size&);

	/**
	 * @brief 获取缓冲区大小.
	 */
	const Size& getSize();

private:
	Framebuffer* current;
	Framebuffer* next;
	Framebuffer buffer[2];
};

#endif // !CLEM_RENDERER_RENDERER_H_
