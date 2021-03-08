// Copyright 2020 SMS
// License(Apache-2.0)
// 摄像机

#include "camera.h"
#include <vector>
#include <algorithm>
#include <cassert>
#include "cursor.h"
#include "scene.h"
#include "factor.h"

using std::vector;

Camera::Camera()
		: Camera(nullptr)
{
}

Camera::Camera(Scene* s)
	: scene(s), depth(0)
{
}

void Camera::render()
{
	Texture buffer(size);

	Rect inputRect(inPos, size);

	for(auto f : scene->getFactors())
		if(inputRect.contains(Rect(f->getPosition(), f->getTexture().getSize())))
			buffer.drawTexture(f->getTexture(), f->getPosition());

	auto& buf = buffer.getTiles();
	for(ushort y = 0; y < size.y; y++)
	{
		Cursor::move(0, y);
		for(ushort x = 0; x < size.x; x++)
		{
			buf[y * size.x + x].getColor().on();
			printf("%c", buf[y * size.x + x].getChar());
		}
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
