// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Component.h"
#include "Core/Math/Math.h"
#include "ECS/ECS.h"

namespace clem
{
/**
 * @brief 变换组件.
 */
class Transform
{
    CLEM_DECLARE_TYPE;

public:
    Vector2 translation;
    Vector2 rotation;
    Vector2 scale;

	Matrix4 transform;

    /*
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
	*/
};

CLEM_DEFINE_TYPE(Transform);

} // namespace clem
