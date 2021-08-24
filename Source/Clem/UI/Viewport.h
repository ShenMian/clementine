// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Layer.h"
#include "Rendering/Rendering.h"
#include <filesystem>

namespace fs = std::filesystem;

namespace clem::ui
{

/**
 * @brief 视口面板.
 */
class Viewport : public Layer
{
public:
    void attach() override;
    void update(Time dt) override;

    inline static bool visible = true;

private:
    void render(Time dt);
    void onResize(float x, float y);
    void updateCameraControl(Time dt);
    void updateLight(Time dt);
    void updateShadow(Time dt);
    void updateCamera(Time dt);

    Camera                       camera;
    std::shared_ptr<Shader>      standardShader, shadowShader, skyboxShader;
    std::shared_ptr<Texture2D>   texture;
    bool                         hovered, locked = false;
    Vector2                      viewportSize;
    std::shared_ptr<FrameBuffer> framebuffer = FrameBuffer::create({(int)(1920 * 0.7), (int)(1080 * 0.7)},
                                                                   {FrameBuffer::PixelFormat::RGBA8,
                                                                    FrameBuffer::PixelFormat::RGBA8,
                                                                    FrameBuffer::PixelFormat::R8,
                                                                    FrameBuffer::PixelFormat::Depth24Stencil8});
    std::shared_ptr<FrameBuffer> shadowMap    = FrameBuffer::create({1024, 1024}, {FrameBuffer::PixelFormat::DepthComponent});
};

} // namespace clem::ui