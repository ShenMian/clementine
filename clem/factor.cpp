// Copyright 2020 SMS
// License(Apache-2.0)
// 游戏对象

#include "factor.h"
#include "scene.h"
#include "component.h"
#include "physics/collider.h"
#include <algorithm>
#include <cassert>

/**
 * @brief 构造 Factor 对象
 * 
 */
Factor::Factor()
		: scene(nullptr)
{
}

/**
 * @brief 构造 Factor 对象
 * 
 * @param s 所属场景
 */
Factor::Factor(Scene& s)
{
	s.addFactor(*this);
}

/**
 * @brief 更新组件
 * 
 * @param dt 
 */
void Factor::update(float dt)
{
	for(auto c : components)
		c->update(dt);
}

/**
 * @brief 添加组件
 * 
 * @param com 组件
 */
void Factor::addComponent(Component& com)
{
	com.setOwner(this);
	com.onAdd();
	components.push_back(&com);
}

/**
 * @brief 移除组件
 * 
 * @param com 组件
 */
void Factor::removeComponent(Component& com)
{
	auto it = std::find(components.begin(), components.end(), &com);
	if(it != components.end())
	{
		(*it)->onRemove();
		(*it)->setOwner(nullptr);
		components.erase(it);
	}
	else
		assert(false);
}

void Factor::setScene(Scene* s)
{
	scene = s;
}

Scene* Factor::getScene() const
{
	return scene;
}

/**
 * @brief 设置坐标
 * 
 * @param p 坐标
 */
void Factor::setPosition(const Point& p)
{
	this->position = p;
}

/**
 * @brief 获得坐标
 * 
 * @return const Point& 坐标
 */
const Point& Factor::getPosition() const
{
	return position;
}

/**
 * @brief 回调, 当碰撞体发生碰撞时
 */
void Factor::onCollision(Collider&, Collider&)
{
}
