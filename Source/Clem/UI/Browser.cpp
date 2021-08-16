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
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4());
            if(ImGui::ImageButton(folderIcon->getHandle(), {48, 48}, {0, 1}, {1, 0}))
                current = entry;
            ImGui::TextWrapped(filename.c_str());
            ImGui::PopStyleColor();
        }
        else
        {
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4());
            ImGui::ImageButton(fileIcon->getHandle(), {48, 48}, {0, 1}, {1, 0});
            ImGui::TextWrapped(filename.c_str());
            ImGui::PopStyleColor();
        }
        ImGui::NextColumn();
    }

    ImGui::End();
}

} // namespace clem::ui