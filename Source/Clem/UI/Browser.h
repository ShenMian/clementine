// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Layer.h"
#include "Rendering/Rendering.h"
#include <filesystem>

namespace fs = std::filesystem;

namespace clem::ui
{

class Browser : public Layer
{
    void update(Time dt) override;

private:
    fs::path                   assets     = "assets";
    fs::path                   current    = "assets";
    std::shared_ptr<Texture2D> fileIcon   = Texture2D::create("../assets/textures/file_icon.png");
    std::shared_ptr<Texture2D> folderIcon = Texture2D::create("../assets/textures/folder_icon.png");

    bool visible = true;
};

} // namespace clem::ui