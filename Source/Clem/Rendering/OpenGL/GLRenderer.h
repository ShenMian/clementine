// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "GLCommandBuffer.h"
#include "Rendering/Renderer.h"

namespace clem
{

void GLCheckError();
void GLClearError();

#define GLCall(func)    \
    do                  \
    {                   \
        GLClearError(); \
        func;           \
        GLCheckError(); \
    } while(false)

class Model;
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

    void beginFrame() override;
    void endFrame() override;
    void submit(const Entity& entity) override;
    void submit(const Entity& entity, std::shared_ptr<Shader> shader) override;
    void submit(std::shared_ptr<VertexArray> vertexArray, std::shared_ptr<Shader> shader, const Matrix4& transform) override;
    void setViewport(int x, int y, int width, int height) override;

    void init() override;
    void deinit() override;

private:
    GLRenderer() = default;

    std::shared_ptr<CommandBuffer> cmdBuffer;
};

/**
 * end of Rendering group
 * @}
 */

} // namespace clem