// Copyright 2020 SMS
// License(Apache-2.0)
// 场景摄像机

#include "camera.h"
#include <vector>
#include <algorithm>
#include <assert.h>
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
	assert(size.area() != 0);

	Texture texture(size);

	for(auto f : scene->getFactors())
		if(true)
			texture.drawTexture(f->getTexture(), f->getPosition() - inPos);

	for(ushort y = 0; y < size.y; y++)
	{
		printf("\x1b[%d;%dH", (int)outPos.x, (int)outPos.y + y);
		for(ushort x = 0; x < size.x; x++)
			printf("%s", texture.at(Point(x, y)).getString().c_str());
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

