// Copyright 2021 SMS
// License(Apache-2.0)

#include "Hierarchy.h"

namespace clem::ui
{

void Hierarchy::update(Time dt)
{
    if(!visible)
        return;

    ImGui::Begin("Hierarchy", &visible);

    if(ImGui::CollapsingHeader("Tagged", ImGuiTreeNodeFlags_DefaultOpen))
        Main::registry.each<Tag>([this](const auto e)
                                 { showEntity(e); });

    if(ImGui::CollapsingHeader("Untagged", ImGuiTreeNodeFlags_DefaultOpen))
        Main::registry.all([this](const auto e)
                           {
                               if(e.noneOf<Tag>())
                                   showEntity(e);
                           });

    // 空白区域右键
    if(ImGui::BeginPopupContextWindow(0, 1, false))
    {
        if(ImGui::MenuItem("Create Empty"))
            Main::registry.create().add<Transform>();
        if(ImGui::BeginMenu("3D Model"))
        {
            if(ImGui::MenuItem("Cube"))
            {
                auto entity = Main::registry.create();
                entity.add<Transform>();
                entity.add<Model>("../assets/models/cube.obj");
            }

            if(ImGui::MenuItem("Sphere"))
            {
                auto entity = Main::registry.create();
                entity.add<Transform>();
                entity.add<Model>("../assets/models/sphere/sphere.obj");
            }

            if(ImGui::MenuItem("Cone"))
            {
                auto entity = Main::registry.create();
                entity.add<Transform>();
                entity.add<Model>("../assets/models/cone.obj");
            }

            ImGui::EndMenu();
        }
        ImGui::EndPopup();
    }

    // 空白区域左键
    if(ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
        Properties::entity = Entity();

    ImGui::End();
}

void Hierarchy::showEntity(const Entity& e)
{
    auto flags = (Properties::entity == e ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
    bool open;
    if(e.anyOf<Tag>())
        open = ImGui::TreeNodeEx((void*)(intptr_t)e.id(), flags, e.get<Tag>().str.c_str());
    else
        open = ImGui::TreeNodeEx((void*)(intptr_t)e.id(), flags, std::to_string(e.id()).c_str());

    if(ImGui::IsItemClicked())
        Properties::entity = e;
    if(open)
        ImGui::TreePop();

    if(ImGui::BeginPopupContextItem())
    {
        if(ImGui::MenuItem("Delete"))
            Main::registry.destroy(e);
        ImGui::EndPopup();
    }
}

} // namespace clem::ui