// Copyright 2021 SMS
// License(Apache-2.0)

#ifndef CLEM_RENDERER_H_
#define CLEM_RENDERER_H_

#include "Clem/Math/Vec2.h"
#include <vector>

class Tile;
class Sprite;

class Framebuffer
{
	class buffer_t;

public:
	void drawPoint(const Point& position, const Tile&);
	void drawSprite(const Point& positon, const Sprite& sprite);

private:
	std::vector<buffer_t> buffer;
};

#endif // !CLEM_RENDERER_H_
