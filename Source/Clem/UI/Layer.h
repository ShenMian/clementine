// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Core/Core.h"

#define LEFT_LABEL(func, label, ...) (ImGui::TextUnformatted(label), ImGui::SameLine(), func("##" label, __VA_ARGS__))

namespace clem::ui
{

class Layer
{
public:
    virtual void update(Time dt) = 0;
    virtual void attach();
    virtual void detach();
};

} // namespace clem::ui