// Copyright 2021 SMS
// License(Apache-2.0)

#include "Framebuffer.h"
#include "Clem/Platform.h"

#ifdef OS_UNIX

typedef Tile buffer_t;

void Framebuffer::drawSprite(const Point& positon, const Sprite&)
{
}

#endif

#ifdef OS_WIN

typedef CHAR_INFO buffer_t;

void Framebuffer::drawSprite(const Point& p, const Sprite& s)
{
	
}

#endif
