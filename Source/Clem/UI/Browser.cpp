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

Browser::Browser()
{
    assets  = Application::get().getAssetPath();
    current = assets;

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
    PROFILE_FUNC();

    assert(fs::exists(assets) && fs::exists(current));

    if(!visible)
        return;

    ImGui::Begin("Browser", &visible);

    if(ImGui::Button("<"))
        if(current != assets)
            current = current.parent_path();
    ImGui::SameLine();
    ImGui::Text("%s", current.string().c_str());

    std::shared_ptr<Texture2D> icon;
    auto                       columnsNum = std::max((int)(ImGui::GetContentRegionAvailWidth() / 70), 1);
    ImGui::Columns(columnsNum);
    for(const auto& entry : fs::directory_iterator(current))
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
                current = entry;
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