// Copyright 2020 SMS
// License(Apache-2.0)
// 摄像机

#include "camera.h"
#include <vector>
#include <algorithm>
#include <cassert>
#include "cursor.h"
#include "scene.h"
#include "sprite.h"
#include "factor.h"
#include "frame_buffer.h"

using std::vector;

Camera::Camera()
		: Camera(nullptr)
{
}

Camera::Camera(Scene* s)
	: scene(s), depth(0)
{
}

void Camera::render(const vector<Sprite*>& sprites)
{
	Rect viewport(inPos, size);
	for(auto s : sprites)
	{
		auto& pos  = s->getOwner()->getPosition();
		auto  size = s->getSize();
		Rect box(pos, size);
		if(!viewport.contains(box))
			continue;
		for(int y = 0; y < size.y; y++)
			for(int x = 0; x < size.x; x++)
				frameBuffer.drawPoint({pos.x + x, pos.y + y}, s->buffer[0]);
	}
}

void Camera::setScene(Scene* s)
{
	assert(s != nullptr);
	scene = s;
}

Scene* Camera::getScene() const
{
	return scene;
}

void Camera::setInputPosition(const Point& p)
{
	inPos = p;
}

void Camera::setOutputPosition(const Point& p)
{
	outPos = p;
}

void Camera::setSize(Size s)
{
	size = s;
}

Size Camera::getSize() const
{
	return size;
}

void Camera::setDepth(ushort d)
{
	depth = d;
	if(scene)
	{
		scene->removeCamera(*this);
		scene->addCamera(*this);
	}
}

ushort Camera::getDepth() const
{
	return depth;
}
