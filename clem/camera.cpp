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

/**
 * @brief 渲染视野内的画面
 * 
 * @param sprites 所有可能出现的画面
 */
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

/**
 * @brief 设置所属场景
 * 
 * @param s 所属场景
 */
void Camera::setScene(Scene* s)
{
	assert(s != nullptr);
	scene = s;
}

/**
 * @brief 获取所属场景
 * 
 * @return Scene* 所属场景
 */
Scene* Camera::getScene() const
{
	return scene;
}

/**
 * @brief 设置输入区域左上角坐标
 * 
 * @param p 
 */
void Camera::setInputPosition(const Point& p)
{
	inPos = p;
}

/**
 * @brief 设置输出区域左上角坐标
 * 
 * @param p 
 */
void Camera::setOutputPosition(const Point& p)
{
	outPos = p;
}

/**
 * @brief 设置视野大小
 * 
 * @param s 
 */
void Camera::setSize(Size s)
{
	size = s;
}

/**
 * @brief 获取视野大小
 * 
 * @return Size 
 */
Size Camera::getSize() const
{
	return size;
}

/**
 * @brief 设置深度, 深度越低越先渲染
 * 
 * @param d 
 */
void Camera::setDepth(ushort d)
{
	depth = d;
	if(scene)
	{
		scene->removeCamera(*this);
		scene->addCamera(*this);
	}
}

/**
 * @brief 获取深度
 * 
 * @return ushort 
 */
ushort Camera::getDepth() const
{
	return depth;
}
