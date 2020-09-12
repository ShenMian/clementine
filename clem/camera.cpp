// Copyright 2020 SMS
// License(Apache-2.0)
// 场景摄像机

#include "camera.h"
#include <vector>
#include <algorithm>
#include "renderer.h"
#include "entity.h"

using std::vector;

Camera::Camera(Scene& scene)
		: scene(scene), depth(0)
{
}

void Camera::render(Renderer& renderer, const vector<Entity*>& objs)
{
	for(auto obj : objs)
		if(inSight(*obj))
			renderer.draw(obj->getTexture(), obj->getPosition());
	renderer.render(outputRect);
	renderer.clear();
}

void Camera::setInputRect(const Rect& rect)
{
	inputRect = rect;
}

void Camera::setOutputRect(const Rect& rect)
{
	outputRect = rect;
}

bool Camera::inSight(const Entity& obj) const
{
	auto pos = obj.getPosition();
	if(inputRect.x < pos.x && pos.x < inputRect.right() &&
		 inputRect.y < pos.y && pos.y < inputRect.bottom())
		return true;
	else
		return false;
}
