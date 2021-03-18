// Copyright 2021 SMS
// License(Apache-2.0)

#include "Renderer.h"
#include "Clem/Profiler.h"

Renderer::Renderer()
{
	current = &buffer[0];
	next    = &buffer[1];
}

Renderer& Renderer::getInstance()
{
	static Renderer instance;
	return instance;
}

void Renderer::render()
{
	PROFILE_FUNC();

	current->render();
}

void Renderer::swapBuffers()
{
	PROFILE_FUNC();

	auto t  = current;
	current = next;
	next    = t;
}

Framebuffer& Renderer::getBuffer() const
{
	return *next;
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
