// Copyright 2021 SMS
// License(Apache-2.0)

#ifndef CLEM_RENDERER_RENDERER_H_
#define CLEM_RENDERER_RENDERER_H_

#include "Framebuffer.h"
#include "Clem/Math/Vec2.h"

class Renderer
{
public:
	static Renderer& getInstance();

	void render();

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
	void setSize(const Size&);

	/**
	 * @brief ��ȡ��������С.
	 */
	const Size& getSize();

private:
	Renderer();

	Framebuffer* current;
	Framebuffer* next;
	Framebuffer buffer[2];
};

#endif // !CLEM_RENDERER_RENDERER_H_
