﻿// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Core/Math/Math.h"
#include "ECS/ECS.h"
#include "Component.h"

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
