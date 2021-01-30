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
	static Texture buffer;

	// 渲染
	if(buffer.getSize() != size)
		buffer.setSize(size);

	Rect inputRect(inPos, size);

	for(auto f : scene->getFactors())
		buffer.drawTexture(f->getTexture(), {0, 0});

	// 输出
#ifndef OS_WIN
	for(short y = 0; y < size.y; y++)
	{
		Cursor::moveTo(0, y);
		for(short x = 0; x < size.x; x++)
			printf("%s", buffer.at(x, y).getString().c_str());
	}
#endif

#ifdef OS_WIN
	static auto lastSize = size;
	if(lastSize != size)
		assert(false);
	static char* buf = new char(size.area());
	for(short y = 0; y < size.y; y++)
	{
		Cursor::moveTo(0, y);
		for(short x = 0; x < size.x; x++)
			printf("%s", buffer.at(x, y).getString().c_str());
	}
	WriteConsole(
		Windows::getStdOut(),
		buf,
		size.area();
  	NULL,
		NULL
	);
#endif
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
