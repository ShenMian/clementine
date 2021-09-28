// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Layer.h"
#include "Rendering/Rendering.h"
#include "Core/Core.h"
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
    enum class Status
    {
        Playing,
        Stopping
    };

    void attach() override;
    void update(Time dt) override;

    inline static bool visible = true;

private:
    void deferredRender(Time dt);
    void forwardRender(Time dt);
    void toolbar();
    void gizmos(const Vector2& pos, const Vector2& size);
    void mousePicking(const Vector2& pos);
    void playScene();
    void stopScene();

    void onResize(float x, float y);
    void updateCameraControl(Time dt);
    void updateShadow(Time dt);
    void updateCamera(Time dt);

    void uploadLights(std::shared_ptr<Shader> shader);

    Status                  status  = Status::Stopping;
    GBuffer                 gbuffer = GBuffer(Configuration::displayResolution);
    std::shared_ptr<Shader> geomertyPass, lightingPass;

    Camera                       camera;
    std::shared_ptr<Shader>      forwardShader, shadowShader, skyboxShader;
    bool                         hovered, locked = false;
    Vector2                      viewportSize;
    std::shared_ptr<FrameBuffer> framebuffer = FrameBuffer::create(Configuration::displayResolution,
                                                                   {FrameBuffer::PixelFormat::RGBA8,
                                                                    FrameBuffer::PixelFormat::R8,
                                                                    FrameBuffer::PixelFormat::DepthStencil});
    std::shared_ptr<FrameBuffer> shadowMap   = FrameBuffer::create({1024, 1024}, {FrameBuffer::PixelFormat::Depth});

    std::vector<DirectionLight> dirLights;
    std::vector<PointLight>     pointLights;
    std::vector<SpotLight>      spotLights;
};

} // namespace clem::ui