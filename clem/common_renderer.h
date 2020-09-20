// Copyright 2020 SMS
// License(Apache-2.0)
// 通用渲染器

#ifndef CLEM_COMMON_RENDERER_H_
#define CLEM_COMMON_RENDERER_H_

#include <vector>
#include "renderer.h"
#include "texture.h"

class CommonRenderer : public Renderer
{
public:
	CommonRenderer(const Size& size);

  void render(const Rect& rect) const override;
	void draw(const Texture& texture, const Point& coord) override;

private:
	Size    size;
	Texture buffer;
};

#endif // CLEM_COMMON_RENDERER_H_
