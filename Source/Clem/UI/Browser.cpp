// Copyright 2021 SMS
// License(Apache-2.0)

#include "Browser.h"
#include <glad/glad.h>
#include <imgui/imgui.h>

namespace clem::ui
{

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

    ImGui::Columns((int)(ImGui::GetContentRegionAvail().x / 70));

    for(const auto& entry : fs::directory_iterator(current))
    {
        auto filename = entry.path().filename().string();
        if(entry.is_directory())
        {
            ImGui::PushID(filename.c_str());
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4());
            if(ImGui::ImageButton((ImTextureID)folderIcon->getHandle(), {48, 48}, {1, 0}, {0, 1}))
                current = entry;
            ImGui::TextWrapped(filename.c_str());
            ImGui::PopStyleColor();
            ImGui::PopID();
        }
        else
        {
            ImGui::PushID(filename.c_str());
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4());
            ImGui::ImageButton((ImTextureID)fileIcon->getHandle(), {48, 48}, {1, 0}, {0, 1});

            if(ImGui::BeginDragDropSource())
            {
                ImGui::SetDragDropPayload("browser", entry.path().string().c_str(), entry.path().string().size() * sizeof(char));
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