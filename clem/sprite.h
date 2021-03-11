// Copyright 2020 SMS
// License(Apache-2.0)
// Í¼Ïñ

#ifndef CLEM_SPRITE_H_
#define CLEM_SPRITE_H_

#include "clem/component.h"
#include <string>
#include <vector>

class FrameBuffer;

class Sprite : public Component
{
public:
	void setSize(Size);
	Size getSize() const;

	void onAdd() override;
	void onRemove() override;

private:
	Size              size;
	std::vector<Tile> buffer;
};

#endif // !CLEM_SPRITE_H_
