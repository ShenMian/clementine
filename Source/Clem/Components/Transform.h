// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Clem/Core/Math/Math.h"
#include "Clem/ECS/config.h"
#include "Component.h"

namespace clem
{
/**
 * @brief 变换组件.
 */
class Transform : public Component
{
	CLEM_DECLARE_TYPE;

public:
	void   setPosition(const Point2&);
	Point2 getPosition() const;

	Point2 getWorldPosition();

	void setDirty(bool);
	bool isDirty() const;

	void       setParent(Transform*);
	Transform* getParent() const;

private:
	Vector2    local;
	Vector2    world;
	bool       dirty  = true;
	Transform* parent = nullptr;
};

CLEM_DEFINE_TYPE(Transform);

} // namespace clem
