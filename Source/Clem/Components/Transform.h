// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Clem/Core/Math/Math.h"
#include "Component.h"

namespace clem
{
/**
 * @brief 变换组件.
 */
class Transform : public Component
{
public:
	void   setPosition(const Point2&);
	Point2 getPosition() const;

	Point2 getWorldPosition();

	bool       dirty  = true;
	Transform* parent = nullptr;

private:
	Vector2    position;
	Vector2    worldPosition;
};
} // namespace clem
