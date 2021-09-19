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

/**
 * @brief 项目文件浏览面板.
 *
 * 管理当前项目具有的各种资源.
 */
class Browser : public Layer
{
public:
    Browser();

    void update(Time dt) override;

    inline static bool visible = true;

private:
    void refresh();

    void showFileIcons(); // 以图标形式显示文件
    void showFileList();  // 以列表形式显示文件
    void showFileNode(const std::filesystem::directory_entry& entry);
    void fileDragDrop(const std::filesystem::path& path, std::shared_ptr<Texture2D> icon);

    fs::path                                                    current;
    std::vector<fs::directory_entry>                            cache;
    std::unordered_map<std::string, std::shared_ptr<Texture2D>> icons;
};

} // namespace clem::ui