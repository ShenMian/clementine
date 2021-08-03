// Copyright 2021 SMS
// License(Apache-2.0)

#include "Output.h"
#include "Profiler.h"

namespace clem
{
Output::Output()
{
	front = &buffer[0];
	back  = &buffer[1];
}

Output& Output::get()
{
	static Output instance;
	return instance;
}

void Output::update()
{
	front->output();
}

void Output::swapBuffers()
{
	auto t = front;
	front  = back;
	back   = t;
}

Framebuffer& Output::getBuffer() const
{
	return *back;
}

void Output::setSize(const Size2i& s)
{
	buffer[0].setSize(s);
	buffer[1].setSize(s);
}

const Size2i& Output::getSize()
{
	return buffer[0].getSize();
}
} // namespace clem