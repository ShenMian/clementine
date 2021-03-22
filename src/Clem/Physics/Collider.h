// Copyright 2021 SMS
// License(Apache-2.0)

#ifndef CLEM_COLLIDER_H_
#define CLEM_COLLIDER_H_

#include "Clem/Math/Vec2.h"

class Rigidbody;
class BoxCollider;
class CircleCollider;

/**
 * @addtogroup Physics
 * @{
 */

/**
 * @brief 碰撞体.
 */
class Collider
{
public:
	Collider() = default;

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
	Rigidbody* owner = nullptr;
};

/**
 * end of Physics group
 * @}
 */

#endif // !CLEM_COLLIDER_H_
