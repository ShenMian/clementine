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
		buffer.drawTexture(f->getTexture(), f->getPosition());

	buffer.render(Rect(outPos, size));
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
