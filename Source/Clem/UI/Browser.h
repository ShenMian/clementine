// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Layer.h"
#include "Rendering/Rendering.h"
#include <filesystem>

#include "Rendering/OpenGL/GLFrameBuffer.h"

namespace fs = std::filesystem;

namespace clem::ui
{

class Browser : public Layer
{
public:
    void update(Time dt) override;

    inline static bool     visible = true;
    inline static fs::path assets  = "../assets"; // 当前项目根目录

private:
    fs::path                   current    = assets;
    std::shared_ptr<Texture2D> fileIcon   = Texture2D::create("../assets/textures/file_icon.png");
    std::shared_ptr<Texture2D> folderIcon = Texture2D::create("../assets/textures/folder_icon.png");
};

} // namespace clem::ui