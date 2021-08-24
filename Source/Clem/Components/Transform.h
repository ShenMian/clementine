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
    Vector3 translation;
    Vector3 rotation; // 单位: 角度.
    Vector3 scale = {1.f, 1.f, 1.f};

    operator Matrix4();

    Matrix4 getModelMatrix();

private:
    bool isDirty() const;

    Matrix4 model;
    Vector3 lastTranslation;
    Vector3 lastRotation;
    Vector3 lastScale;
};

CLEM_DEFINE_TYPE(Transform);

} // namespace clem
