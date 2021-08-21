// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Layer.h"
#include "Rendering/Rendering.h"
#include <filesystem>

namespace fs = std::filesystem;

namespace clem::ui
{

class Viewport : public Layer
{
public:
    void update(Time dt) override;
    void attach() override;

    void render(Time dt);

    inline static bool visible = true;

private:
    void onResize();

    Camera                       camera;
    Matrix4                      light;
    std::shared_ptr<Shader>      standardShader, skyboxShader;
    std::shared_ptr<Texture2D>   texture;
    std::shared_ptr<FrameBuffer> framebuffer = FrameBuffer::create({1920 * 0.7, 1080 * 0.7},
                                                                   {FrameBuffer::PixelFormat::Auto, FrameBuffer::PixelFormat::Auto, FrameBuffer::PixelFormat::I8});
    bool                         activated, locked = false;
    Vector3                      move;
};

} // namespace clem::ui