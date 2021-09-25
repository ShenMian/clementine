// Copyright 2021 SMS
// License(Apache-2.0)

#include "Dockspace.h"
#include "Browser.h"
#include "Hierarchy.h"
#include "Profiler.h"
#include "Properties.h"
#include <glad/glad.h>
#include <imgui/imgui.h>

namespace clem::ui
{

void Dockspace::update(Time dt)
{
    PROFILE_FUNC();

    if(!visible)
        return;

    if(ImGui::GetIO().ConfigFlags & ~ImGuiConfigFlags_DockingEnable)
        return;

    if(ImGui::BeginMainMenuBar())
    {
        if(ImGui::BeginMenu("View"))
        {
            ImGui::MenuItem("Hierarchy", nullptr, &Hierarchy::visible);
            ImGui::MenuItem("Properties", nullptr, &Properties::visible);
            ImGui::MenuItem("Browser", nullptr, &Browser::visible);
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    // �������Ǵ��ڵ� UI �������
    bool fullWindow = true; // ʹ�������ڳ�Ϊ dockspace

    auto dockspaceFlags = ImGuiDockNodeFlags_None;
    auto windowFlags    = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    if(fullWindow)
    {
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        windowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }
    if(dockspaceFlags & ImGuiDockNodeFlags_PassthruCentralNode)
        windowFlags |= ImGuiWindowFlags_NoBackground;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("Dock space", &visible, windowFlags);
    ImGui::PopStyleVar();

    if(fullWindow)
        ImGui::PopStyleVar(2);

    ImGui::DockSpace(ImGui::GetID("dock_space"), ImVec2(0.0f, 0.0f), dockspaceFlags);

    ImGui::End();
}

} // namespace clem::ui