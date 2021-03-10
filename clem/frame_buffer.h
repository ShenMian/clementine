// Copyright 2020 SMS
// License(Apache-2.0)
// Ö¡»º³åÇø

#ifndef CLEM_FRAME_BUFFER_H_
#define CLEM_FRAME_BUFFER_H_

#include "platform.h"
#include "type.h"

class Tile;

class FrameBuffer
{
	#ifdef OS_WIN
		typedef CHAR_INFO buffer_t;
	#else
    typedef char buffer_t;
  #endif


public:
	FrameBuffer();
	FrameBuffer(Size);
	~FrameBuffer();

	void drawPoint(Point, const Tile&);
	void drawLine(Point, Point, const Tile&);
	void drawRect(Rect, const Tile&);
	void drawRectFill(Rect, const Tile&);
	void drawCycle(Point, short radius, const Tile&);

	void setSize(Size);
	void swapBuffer();
	void render();

private:
	buffer_t* current;
	buffer_t* next;
	Size      size;
};

#endif // !CLEM_FRAME_BUFFER_H_
