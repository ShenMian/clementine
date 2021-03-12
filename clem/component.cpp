// Copyright 2020 SMS
// License(Apache-2.0)
// 组件

#include "component.h"

Component::Component()
		: owner(nullptr)
{
}

void Component::update(float)
{
}

/**
 * @brief 回调, 当组件被添加
 */
void Component::onAdd()
{
}

/**
 * @brief 回调, 当组件被移除
 */
void Component::onRemove()
{
}

/**
 * @brief 设置拥有者
 * 
 * @param o 拥有者
 */
void Component::setOwner(Factor* o)
{
	this->owner = o;
}

/**
 * @brief 获取拥有者
 * 
 * @return Factor* 拥有者
 */
Factor* Component::getOwner() const
{
	return owner;
}
