// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "ECS/Entity.h"
#include "Layer.h"
#include "Properties.h"
#include <glad/glad.h>
#include <imgui/imgui.h>

namespace clem::ui
{

class Hierarchy : public Layer
{
public:
    void update(Time dt) override;

    inline static bool visible = true;

private:
    void showEntity(const Entity& e);
};

} // namespace clem::ui