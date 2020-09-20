// Copyright 2020 SMS
// License(Apache-2.0)
// ÎÞÉ«²ÊäÖÈ¾Æ÷

#ifndef CLEM_NOCOLOR_RENDERER_H_
#define CLEM_NOCOLOR_RENDERER_H_

#include "renderer.h"
#include <vector>

class NocolorRenderer : public Renderer
{
public:
	void render(const Rect& rect) const;
	void draw(const Texture& texture, const Point& pos);
};

#endif // CLEM_NOCOLOR_RENDERER_H_
