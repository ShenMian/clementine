// Copyright 2020 SMS
// License(Apache-2.0)
// 渲染器

#ifndef CLEM_RENDERER_H_
#define CLEM_RENDERER_H_

#include <vector>

class Rect;
class Point;
class Texture;

class Renderer
{
public:
  virtual void render(const Rect&) const;
	virtual void draw(const Texture&, const Point&);
  virtual void clear();

protected:
	std::vector<const Texture*> textures;
};

#endif // CLEM_RENDERER_H_
