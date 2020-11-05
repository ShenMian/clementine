// Copyright 2020 SMS
// License(Apache-2.0)
// 场景摄像机

#include "camera.h"
#include <vector>
#include <algorithm>
#include <assert.h>
#include "scene.h"
#include "director.h"
#include "factor.h"

using std::vector;

Renderer Camera::renderer;

Camera::Camera()
		: scene(nullptr), depth(0)
{
}

void Camera::render()
{
	for(auto f : scene->getFactors())
		if(true)
			renderer.drawTexture(f->getTexture(), f->getPosition());
}

void Camera::setScene(Scene* s)
{
	assert(s != nullptr);
	scene = s;
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

void Camera::setDepth(ushort depth)
{
	this->depth = depth;
}

ushort Camera::getDepth() const
{
	return depth;
}

