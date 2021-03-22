// Copyright 2021 SMS
// License(Apache-2.0)

#include "Renderer.h"
#include "Clem/Profiler.h"

Renderer::Renderer()
{
	front = &buffer[0];
	back  = &buffer[1];
}

Renderer& Renderer::getInstance()
{
	static Renderer instance;
	return instance;
}

void Renderer::output()
{
	PROFILE_FUNC();

	front->output();
}

void Renderer::swapBuffers()
{
	PROFILE_FUNC();

	auto t = front;
	front  = back;
	back   = t;
}

Framebuffer& Renderer::getBuffer() const
{
	return *back;
}

void Renderer::setSize(const Size& s)
{
	buffer[0].setSize(s);
	buffer[1].setSize(s);
}

const Size& Renderer::getSize()
{
	return buffer[0].getSize();
}
