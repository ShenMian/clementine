// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Layer.h"
#include "Rendering/Rendering.h"

namespace clem::ui
{

class Dockspace : public Layer
{
    void update(Time dt) override;

private:
    bool visible = true;
};

} // namespace clem::ui