// Copyright 2020 SMS
// License(Apache-2.0)
// 场景摄像机

#include "camera.h"
#include <vector>
#include <algorithm>
#include <cassert>
#include <clem/cursor.h>
#include "scene.h"
#include "factor.h"
#include "director.h"

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
	static Texture buffer;

	// 渲染
	if(buffer.getSize() != size)
		buffer.setSize(size);

	Rect inputRect(inPos, size);

	for(auto f : scene->getFactors())
		buffer.drawTexture(f->getTexture(), {0, 0});

	// 输出
	for(ushort y = 0; y < size.y; y++)
	{
		Cursor::moveTo(0, y);
		for(ushort x = 0; x < size.x; x++)
			printf("%s", buffer.at(x, y).getString().c_str());
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
}

ushort Camera::getDepth() const
{
	return depth;
}
