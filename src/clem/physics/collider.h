// Copyright 2021 SMS
// License(Apache-2.0)

#ifndef CLEM_COLLIDER_H_
#define CLEM_COLLIDER_H_

#include "clem/Math/Point.h"

class Rigidbody;
class BoxCollider;
class CircleCollider;

/**
 * @addtogroup physics
 * @{
 */

/// 碰撞体
class Collider
{
public:
	Collider();
	virtual ~Collider();
	
	/**
	 * @brief 检测是否与其他碰撞体发生碰撞.
	 * 
	 * @param other 其他碰撞体.
	 * @return true 发生碰撞.
	 * @return false 未发生碰撞.
	 */
	virtual bool collides(const Collider& other) const = 0;

	/**
	 * @brief 获取坐标.
	 */
	Point getPosition() const;

	/**
	 * @brief 设置偏移量.
	 */
	void  setOffset(Point offset);

	/**
	 * @brief 获取偏移量.
	 */
	Point getOffset() const;

	void       setOwner(Rigidbody* owner);
	Rigidbody* getOwner() const;

protected:
	Point offset;

private:
	Rigidbody* owner;
};

/**
 * end of physics group
 * @}
 */

#endif // !CLEM_COLLIDER_H_
