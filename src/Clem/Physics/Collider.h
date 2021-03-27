﻿// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Clem/Core/Math/Math.h"

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

	void       setOwner(Rigidbody* owner);
	Rigidbody* getOwner() const;

protected:
	Point2 offset;

private:
	Rigidbody* owner = nullptr;
};

/**
 * end of Physics group
 * @}
 */
