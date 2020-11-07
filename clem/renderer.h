// Copyright 2020 SMS
// License(Apache-2.0)
// 渲染器

#ifndef CLEM_RENDERER_H_
#define CLEM_RENDERER_H_

#include <vector>
#include "texture.h"

class Point;

class Renderer
{
public:
  virtual void render() const;

	virtual void drawTexture(const Texture&texture, const Point& position);
  virtual void clear();

	void setSize(Size size);
	Size getSize() const;

protected:
	Texture texture;
};

#endif // CLEM_RENDERER_H_
