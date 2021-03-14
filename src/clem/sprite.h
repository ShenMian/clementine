// Copyright 2021 SMS
// License(Apache-2.0)
// 图像

#ifndef CLEM_SPRITE_H_
#define CLEM_SPRITE_H_

#include "clem/component.h"
#include "tile.h"
#include <string>
#include <vector>

class FrameBuffer;

/// 图像, 由瓦片组成的图像
class Sprite : public Component
{
	friend class Camera;

public:
	void drawPoint(Point, const Tile&);
	void drawLine(Point, Point, const Tile&);
	void drawRect(Rect, const Tile&);
	void fillRect(Rect, const Tile&);
	void drawCycle(Point, short radius, const Tile&);
	void clear();

	void setSize(Size);
	Size getSize() const;

	void onAdd() override;
	void onRemove() override;

private:
	Size              size;
	std::vector<Tile> buffer;
};

#endif // !CLEM_SPRITE_H_
