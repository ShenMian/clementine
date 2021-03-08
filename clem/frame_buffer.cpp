// Copyright 2020 SMS
// License(Apache-2.0)
// Ö¡»º³åÇø

#include "frame_buffer.h"
#include "type.h"

FrameBuffer::FrameBuffer()
		: buffer(nullptr)
{
}

FrameBuffer::FrameBuffer(Size s)
{
	buffer = new buffer_t[s.area()];
}

FrameBuffer::~FrameBuffer()
{
	delete[] buffer;
}

void FrameBuffer::setSize(Size s)
{
	size = s;

	delete[] buffer;
	buffer = new buffer_t[size.area()]();
}

void FrameBuffer::render(Point pos)
{
	SMALL_RECT writeRegion = {0, 0, pos.x, pos.y};
	WriteConsoleOutputW(GetStdHandle(STD_OUTPUT_HANDLE),
											buffer,
											{size.x, size.y},
											{0, 0},
											&writeRegion);
}
