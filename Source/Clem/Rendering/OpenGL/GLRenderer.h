// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Rendering/Renderer.h"

namespace clem
{

class Shader;
class VertexArray;

/**
 * @addtogroup Rendering
 * @{
 */

class GLRenderer : public Renderer
{
public:
    static GLRenderer& get();

    void submit(std::shared_ptr<VertexArray> vertexArray, std::shared_ptr<Shader> shader);

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