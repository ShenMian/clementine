// Copyright 2021 SMS
// License(Apache-2.0)

#ifndef CLEM_RENDERER_RENDERER_H_
#define CLEM_RENDERER_RENDERER_H_

#include "Clem/Core/Math/Vector2.h"
#include "Framebuffer.h"

class Renderer
{
public:
	static Renderer& getInstance();

	void output();

	/**
	 * @brief ����������.
	 */
	void swapBuffers();

	/**
	 * @brief ��ȡ������.
	 */
	Framebuffer& getBuffer() const;

	/**
	 * @brief ���û�������С.
	 */
	void setSize(const Size2&);

	/**
	 * @brief ��ȡ��������С.
	 */
	const Size2& getSize();

private:
	Renderer();

	Framebuffer* front;
	Framebuffer* back;
	Framebuffer  buffer[2];
};

#endif // !CLEM_RENDERER_RENDERER_H_
