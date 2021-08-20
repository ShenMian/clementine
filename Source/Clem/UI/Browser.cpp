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
    icons["file"]   = Texture2D::create("../assets/textures/icons/file.png");
    icons["folder"] = Texture2D::create("../assets/textures/icons/folder.png");

    icons[".png"] = Texture2D::create("../assets/textures/icons/image.png");
    icons[".jpg"] = Texture2D::create("../assets/textures/icons/image.png");
    icons[".obj"] = Texture2D::create("../assets/textures/icons/3d_object.png");
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

    for(const auto& entry : fs::directory_iterator(current))
    {
        auto filename = entry.path().filename().string();
        if(entry.is_directory())
        {
            ImGui::PushID(filename.c_str());
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4());
            if(ImGui::ImageButton((ImTextureID)icons["folder"]->getHandle(), {48, 48}, {1, 0}, {0, 1}))
                current = entry;
            ImGui::TextWrapped(filename.c_str());
            ImGui::PopStyleColor();
            ImGui::PopID();
        }
        else
        {
            ImGui::PushID(filename.c_str());
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4());

            auto ext = entry.path().extension().string();
            if(icons.contains(ext))
                ImGui::ImageButton((ImTextureID)icons[ext]->getHandle(), {48, 48}, {1, 0}, {0, 1});
            else
                ImGui::ImageButton((ImTextureID)icons["file"]->getHandle(), {48, 48}, {1, 0}, {0, 1});

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