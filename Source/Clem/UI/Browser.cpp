// Copyright 2021 SMS
// License(Apache-2.0)

#include "Browser.h"
#include "Window/GlfwWindow.h"
#include <glad/glad.h>
#include <imgui/imgui.h>

namespace clem::ui
{

void Browser::update(Time dt)
{
    if(!visible)
        return;

    bool open = false;
    ImGui::Begin("Viewport", &open);
    auto framebuffer = FrameBuffer::map["scene"];
    ImGui::Image((ImTextureID) dynamic_cast<GLFrameBuffer*>(framebuffer.get())->colorAttachment, ImGui::GetContentRegionAvail(), {0, 1}, {1, 0}); // FIXME
    ImGui::End();

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