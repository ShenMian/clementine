// Copyright 2020 SMS
// License(Apache-2.0)
// 渲染器

#ifndef CLEM_RENDERER_H_
#define CLEM_RENDERER_H_

#include "type.h"

class Texture;
struct Vector;

class Renderer
{
public:
  virtual void render(const Rect&) const = 0;
	virtual void draw(const Texture&, const Point&) = 0;
  virtual void clear() = 0;
};

#endif // CLEM_RENDERER_H_
