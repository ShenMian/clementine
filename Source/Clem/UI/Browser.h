﻿// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Layer.h"
#include "Rendering/Rendering.h"
#include <filesystem>

#include "Rendering/OpenGL/GLFrameBuffer.h"

namespace fs = std::filesystem;

namespace clem::ui
{

/**
 * @brief 项目文件浏览面板.
 * 管理当前项目具有的各种资源.
 */
class Browser : public Layer
{
public:
    Browser();

    void update(Time dt) override;

    inline static bool     visible = true;
    inline static fs::path assets;

private:
    fs::path current;

    std::unordered_map<std::string, std::shared_ptr<Texture2D>> icons;

    Camera                     camera;
    Matrix4                    light;
    std::shared_ptr<Shader>    standard, skybox;
    std::shared_ptr<Texture2D> texture;
};

} // namespace clem::ui