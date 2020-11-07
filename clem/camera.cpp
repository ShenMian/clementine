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

<<<<<<< HEAD
Camera::Camera(Scene* s)
		: scene(s), depth(0)
=======
Renderer Camera::renderer;

Camera::Camera()
		: scene(nullptr), depth(0)
>>>>>>> bb08b426e997f6b9a83dcf3eed3b18de28ed7221
{
}

void Camera::render()
{
	Texture texture(size);

	puts("A");
	for(auto f : scene->getFactors())
		if(true)
			texture.drawTexture(f->getTexture(), f->getPosition() - inPos);

	puts("B");
	for(ushort y = 0; y < size.y; y++)
	{
		printf("\x1b[%d;%dH", (int)outPos.x, (int)outPos.y + y);
		for(ushort x = 0; x < size.x; x++)
		{
			auto& tile = texture.at(Point(x, y));
			printf("%s", texture.at(Point(x, y)).getString().c_str());
		}
	puts("C");
	}
}

void Camera::setScene(Scene* s)
{
	assert(s != nullptr);
	scene = s;
}

<<<<<<< HEAD
Scene* Camera::getScene() const
{
	return scene;
}

void Camera::setDepth(ushort depth)
=======
void Camera::setInputPosition(const Point& p)
>>>>>>> bb08b426e997f6b9a83dcf3eed3b18de28ed7221
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

