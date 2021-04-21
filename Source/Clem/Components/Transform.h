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
	const Point2& getPosition();

	const Point2& getLocalPosition();
	void          setLocalPosition(const Point2&);

private:
	Vector2    localPosition;
	Vector2    position;
	Transform* parent = nullptr;
	bool       dirty  = true;
};
} // namespace clem
