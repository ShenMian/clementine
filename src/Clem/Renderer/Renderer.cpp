// Copyright 2021 SMS
// License(Apache-2.0)

#include "Renderer.h"

Renderer::Renderer()
{
	current = &buffer[0];
	next    = &buffer[1];
}

void Renderer::render()
{
	current->render();
}

void Renderer::swapBuffer()
{
	auto t  = current;
	current = next;
	next    = t;
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
