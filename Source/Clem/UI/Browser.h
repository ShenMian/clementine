// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Layer.h"
#include "Rendering/Rendering.h"
#include <filesystem>
#include <glad/glad.h>
#include <imgui/imgui.h>

namespace fs = std::filesystem;

namespace clem::ui
{

class Browser : public Layer
{
    void update(Time dt) override
    {
        if(!visible)
            return;

        ImGui::Begin("Browser", &visible);

        assert(fs::exists(assets));
        assert(fs::exists(current));

        if(current != assets)
            if(ImGui::Button("<"))
                current = current.parent_path();

        ImGui::Columns((int)(ImGui::GetContentRegionAvail().x / 80));

        for(const auto& entry : fs::directory_iterator(current))
        {
            auto filename = entry.path().filename().string();
            if(entry.is_directory())
            {
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4());
                if(ImGui::ImageButton(folderIcon->nativeHandle(), {48, 48}, {0, 1}, {1, 0}))
                    current = entry;
                ImGui::TextWrapped(filename.c_str());
                ImGui::PopStyleColor();
            }
            else
            {
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4());
                ImGui::ImageButton(fileIcon->nativeHandle(), {48, 48}, {0, 1}, {1, 0});
                ImGui::TextWrapped(filename.c_str());
                ImGui::PopStyleColor();
            }
            ImGui::NextColumn();
        }

        ImGui::End();
    }

private:
    fs::path                   assets  = "assets";
    fs::path                   current = "assets";
    std::shared_ptr<Texture2D> fileIcon = Texture2D::create("../assets/textures/file_icon.png");
    std::shared_ptr<Texture2D> folderIcon = Texture2D::create("../assets/textures/folder_icon.png");

    bool visible = true;
};

} // namespace clem::ui
