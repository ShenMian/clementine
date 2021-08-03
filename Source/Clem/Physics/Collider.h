// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Core/Math/Math.h"

namespace clem
{
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
	Point2 getPosition() const;

	/**
	 * @brief 设置偏移量.
	 */
	void setOffset(Point2 offset);

	/**
	 * @brief 获取偏移量.
	 */
	Point2 getOffset() const;

	/**
	 * @brief 设置附加到的刚体.
	 */
	void setRigidbody(Rigidbody* rb);

	/**
	 * @brief 获取附加到的刚体.
	 */
	Rigidbody* getRigidbody() const;

protected:
	Point2 offset;

private:
	Rigidbody* rigidbody = nullptr;
};

/**
 * end of Physics group
 * @}
 */

} // namespace clem
