// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Layer.h"
#include "Rendering/Rendering.h"

namespace clem::ui
{

/**
 * @brief 属性面板.
 * 管理指定实体的组件.
 */
class Properties : public Layer
{
public:
    void update(Time dt) override;

    inline static Entity entity;
    inline static bool   visible = true;

private:
    void showTag();
    void showTransform();
    void showRigidbody();
    void showModel();
    void showLight();
    void showMaterial();
    void showSprite();
    void showScript();

    void textureEdit(const std::string& label, std::shared_ptr<Texture2D> texture);
    void vectorEdit(const std::string& label, Vector3& value, float defaultValue = 0.f);
    void colorEdit(const std::string& label, Vector3& value);
};

} // namespace clem::ui