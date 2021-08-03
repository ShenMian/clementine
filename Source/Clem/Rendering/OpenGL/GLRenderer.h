// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Rendering/Renderer.h"

namespace clem
{

/**
 * @addtogroup Rendering
 * @{
 */

class GLRenderer : public Renderer
{
public:
    static GLRenderer& get();

    void init() override;
    void deinit() override;

private:
    GLRenderer() = default;
};

/**
 * end of Rendering group
 * @}
 */

} // namespace clem