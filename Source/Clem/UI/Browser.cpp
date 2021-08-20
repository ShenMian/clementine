// Copyright 2021 SMS
// License(Apache-2.0)

#include "Browser.h"
#include "Window/GlfwWindow.h"
#include <glad/glad.h>
#include <imgui/imgui.h>

namespace clem::ui
{

Browser::Browser()
{
    icons["file"]         = Texture2D::create("../assets/textures/icons/file.png");
    icons["folder"]       = Texture2D::create("../assets/textures/icons/folder.png");
    icons["folder_empty"] = Texture2D::create("../assets/textures/icons/folder_empty.png");

    icons[".png"]  = Texture2D::create("../assets/textures/icons/image.png");
    icons[".jpg"]  = Texture2D::create("../assets/textures/icons/image.png");
    icons[".obj"]  = Texture2D::create("../assets/textures/icons/3d_object.png");
    icons[".vert"] = Texture2D::create("../assets/textures/icons/code.png");
    icons[".frag"] = Texture2D::create("../assets/textures/icons/code.png");
    icons[".wav"]  = Texture2D::create("../assets/textures/icons/audio.png");
}

void Browser::update(Time dt)
{
    if(!visible)
        return;

    ImGui::Begin("Browser", &visible);

    assert(fs::exists(assets));
    assert(fs::exists(current));

    if(current != assets)
        if(ImGui::Button("<"))
            current = current.parent_path();

    ImGui::Columns((int)(ImGui::GetContentRegionAvailWidth() / 70));

    std::shared_ptr<Texture2D> icon;
    for(const auto& entry : fs::directory_iterator(current))
    {
        auto path     = fs::relative(entry.path(), assets);
        auto filename = path.filename().string();

        if(entry.is_directory())
        {
            if(fs::is_empty(path))
                icon = icons["folder_empty"];
            else
                icon = icons["folder"];

            ImGui::PushID(filename.c_str());
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4());
            if(ImGui::ImageButton((ImTextureID)icon->getHandle(), {48, 48}, {1, 0}, {0, 1}))
                current = path;
            ImGui::TextWrapped(filename.c_str());
            ImGui::PopStyleColor();
            ImGui::PopID();
        }
        else
        {
            auto ext = path.extension().string();
            if(icons.contains(ext))
                icon = icons[ext];
            else
                icon = icons["file"];

            ImGui::PushID(filename.c_str());
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4());
            ImGui::ImageButton((ImTextureID)icon->getHandle(), {48, 48}, {1, 0}, {0, 1});

            if(ImGui::BeginDragDropSource())
            {
                const auto     absPath = fs::absolute(entry.path()).wstring();
                const wchar_t* data    = absPath.c_str();
                const size_t   size    = (absPath.size() + 1) * sizeof(wchar_t);
                ImGui::SetDragDropPayload("browser_file", data, size);
                ImGui::TextUnformatted(filename.c_str());
                ImGui::EndDragDropSource();
            }

            ImGui::TextWrapped(filename.c_str());
            ImGui::PopStyleColor();
            ImGui::PopID();
        }
        ImGui::NextColumn();
    }

    ImGui::End();
}

} // namespace clem::ui