// Copyright 2021 SMS
// License(Apache-2.0)
// 碰撞体

#ifndef CLEM_COLLIDER_H_
#define CLEM_COLLIDER_H_

#include "clem/math/point.h"

class Rigidbody;
class BoxCollider;
class CircleCollider;

/// 碰撞体
class Collider
{
public:
	Collider();
	virtual ~Collider();
	
	/**
	 * @brief 检测是否与其他碰撞体发生碰撞
	 * 
	 * @param other 其他碰撞体
	 * @return true 发生碰撞
	 * @return false 未发生碰撞
	 */
	virtual bool collides(const Collider& other) const = 0;

	Point getPosition() const;

	void  setOffset(Point);
	Point getOffset() const;

	void       setOwner(Rigidbody*);
	Rigidbody* getOwner() const;

protected:
	Point offset;

private:
	Rigidbody* owner;
};

#endif // !CLEM_COLLIDER_H_