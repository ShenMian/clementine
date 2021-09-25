// Copyright 2021 SMS
// License(Apache-2.0)

#include "Browser.h"
#include "Core/Application.h"
#include "Profiler.h"
#include "Window/GlfwWindow.h"
#include <glad/glad.h>
#include <imgui/imgui.h>

namespace clem::ui
{

enum class FileDisplayMode
{
    Icon,
    List
};

Browser::Browser()
    : current(Application::get().getAssetPath())
{
    refresh();

    icons["file"]         = Texture2D::create("../assets/textures/icons/file.png");
    icons["folder"]       = Texture2D::create("../assets/textures/icons/folder.png");
    icons["folder_empty"] = Texture2D::create("../assets/textures/icons/folder_empty.png");

    icons[".png"]  = Texture2D::create("../assets/textures/icons/image.png");
    icons[".jpg"]  = Texture2D::create("../assets/textures/icons/image.png");
    icons[".obj"]  = Texture2D::create("../assets/textures/icons/3d_object.png");
    icons[".gltf"] = Texture2D::create("../assets/textures/icons/3d_object.png");
    icons[".vert"] = Texture2D::create("../assets/textures/icons/code.png");
    icons[".frag"] = Texture2D::create("../assets/textures/icons/code.png");
    icons[".wav"]  = Texture2D::create("../assets/textures/icons/audio.png");
}

void Browser::update(Time dt)
{
    PROFILE_FUNC();

    if(!visible)
        return;

    ImGui::Begin("Browser", &visible);

    const auto assets = Application::get().getAssetPath();

    if(ImGui::Button("<") && current != assets)
    {
        current = current.parent_path();
        refresh();
    }
    ImGui::SameLine();
    ImGui::Text("%s", current.string().c_str());

    static FileDisplayMode mode = FileDisplayMode::Icon;
    if(mode == FileDisplayMode::Icon)
        showFileIcons();
    else if(mode == FileDisplayMode::List)
        showFileList();

    // 空白区域右键菜单
    if(ImGui::BeginPopupContextWindow(0, 1, false))
    {
        if(ImGui::BeginMenu("File Display"))
        {
            if(ImGui::MenuItem("Icon"))
                mode = FileDisplayMode::Icon;
            if(ImGui::MenuItem("List"))
                mode = FileDisplayMode::List;

            ImGui::EndMenu();
        }

        ImGui::EndPopup();
    }

    ImGui::End();
}

void Browser::showFileIcons()
{
    std::shared_ptr<Texture2D> icon;

    ImGui::Columns(std::max((int)(ImGui::GetContentRegionAvailWidth() / 70), 1));

    for(const auto& entry : cache)
    {
        auto filename = entry.path().filename().string();

        if(entry.is_directory())
        {
            if(fs::is_empty(entry))
                icon = icons["folder_empty"];
            else
                icon = icons["folder"];

            ImGui::PushID(filename.c_str());
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4());
            if(ImGui::ImageButton((ImTextureID)icon->getHandle(), {48, 48}, {1, 0}, {0, 1}))
            {
                current = entry;
                refresh();

                ImGui::PopStyleColor();
                ImGui::PopID();

                break;
            }
            ImGui::TextWrapped(filename.c_str());
            ImGui::PopStyleColor();
            ImGui::PopID();
        }
        else
        {
            auto ext = entry.path().extension().string();
            if(icons.contains(ext))
                icon = icons[ext];
            else
                icon = icons["file"];

            ImGui::PushID(filename.c_str());
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4());
            ImGui::ImageButton((ImTextureID)icon->getHandle(), {48, 48}, {1, 0}, {0, 1});
            fileDragDrop(entry.path(), icon);
            ImGui::TextWrapped(filename.c_str());
            ImGui::PopStyleColor();
            ImGui::PopID();
        }
        ImGui::NextColumn();
    }
}

void Browser::showFileList()
{
    for(const auto& entry : cache)
        showFileNode(entry);
}

void Browser::showFileNode(const fs::directory_entry& entry)
{
    if(ImGui::TreeNode(entry.path().filename().string().c_str()))
    {
        for(const auto& e : fs::directory_iterator(entry))
        {
            if(e.is_directory())
                showFileNode(e);
            else
            {
                ImGui::Button(e.path().filename().string().c_str());

                std::shared_ptr<Texture2D> icon;
                auto                       ext = e.path().extension().string();
                if(icons.contains(ext))
                    icon = icons[ext];
                else
                    icon = icons["file"];
                fileDragDrop(e, icon);
            }
        }
        ImGui::TreePop();
    }
}

void Browser::fileDragDrop(const fs::path& path, std::shared_ptr<Texture2D> icon)
{
    if(ImGui::BeginDragDropSource())
    {
        const auto     absPath  = fs::absolute(path).wstring();
        const wchar_t* data     = absPath.c_str();
        const size_t   size     = (absPath.size() + 1) * sizeof(wchar_t);
        const auto     filename = path.filename().string();

        ImGui::SetDragDropPayload("browser_file", data, size);
        ImGui::ImageButton((ImTextureID)icon->getHandle(), {48, 48}, {1, 0}, {0, 1});
        ImGui::TextUnformatted(filename.c_str());

        ImGui::EndDragDropSource();
    }
}

void Browser::refresh()
{
    cache.clear();
    for(const auto& entry : fs::directory_iterator(current))
        cache.push_back(entry);
}

} // namespace clem::ui