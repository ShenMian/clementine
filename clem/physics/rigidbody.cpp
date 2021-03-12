// Copyright 2020 SMS
// License(Apache-2.0)
// 刚体

#include "rigidbody.h"
#include "collider.h"

using std::vector;

/**
 * @brief 更新速度和坐标
 * 
 * @param dt 
 */
void Rigidbody::update(float dt)
{
	auto pos = owner->getPosition();
	velocity += accelerate * dt;
	pos += velocity * dt;
	owner->setPosition(pos);
}

/**
 * @brief 添加碰撞体
 * 
 * @param c 碰撞体
 */
void Rigidbody::addCollider(Collider& c)
{
	c.setOwner(this);
	colliders.push_back(&c);
}

/**
 * @brief 获取全部碰撞体
 * 
 * @return const vector<Collider*>& 
 */
const vector<Collider*>& Rigidbody::getColliders() const
{
	return colliders;
}

void Rigidbody::onAdd()
{
	owner->getScene()->addRigidbody(*this);
}

void Rigidbody::onRemove()
{
	owner->getScene()->removeRigidbody(*this);
}
