// Copyright 2020 SMS
// License(Apache-2.0)
// Ö¡»º³åÇø

#include "frame_buffer.h"

FrameBuffer::FrameBuffer()
		: current(nullptr), next(nullptr)
{
}

FrameBuffer::FrameBuffer(Size s)
{
	current = new buffer_t[s.area()]();
	next    = new buffer_t[s.area()]();
}

FrameBuffer::~FrameBuffer()
{
	delete[] current;
	delete[] next;
}

void FrameBuffer::setSize(Size s)
{
	size = s;

	delete[] current;
	delete[] next;
	current = new buffer_t[size.area()]();
	next    = new buffer_t[size.area()]();
}

void FrameBuffer::swapBuffer()
{
	auto temp = current;
	current   = next;
	next      = temp;
}

#ifdef OS_UNIX

void FrameBuffer::render(Point pos)
{
}

#endif

#ifdef OS_WIN

void FrameBuffer::render(Point pos)
{
	SMALL_RECT writeRegion = {0, 0, pos.x, pos.y};
	WriteConsoleOutputW(GetStdHandle(STD_OUTPUT_HANDLE),
											current,
											{(short)size.x, (short)size.y},
											{0, 0},
											&writeRegion);
}

#endif // OS_WIN

