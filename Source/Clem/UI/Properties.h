// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Layer.h"

namespace clem::ui
{

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
    void showSprite();
    void showScript();

    void Vector3Edit(const std::string& label, Vector3& value, float defaultValue = 0.f);
};

} // namespace clem::ui