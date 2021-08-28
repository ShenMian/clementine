// Copyright 2021 SMS
// License(Apache-2.0)

#include "Properties.h"
#include "Browser.h"
#include "Components/Components.h"
#include "Physics/Rigidbody.h"
#include "Profiler.h"
#include <filesystem>
#include <glad/glad.h>
#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
#include <string>

namespace fs = std::filesystem;

namespace clem::ui
{

void Properties::update(Time dt)
{
    PROFILE_FUNC();

    if(!visible)
        return;

    ImGui::Begin("Properties", &visible);

    if(!entity.valid())
    {
        ImGui::End();
        return;
    }

    showTag();
    showTransform();
    showRigidbody();
    showModel();
    showLight();
    showSprite();
    showScript();

    // 空白区域右键菜单
    if(ImGui::BeginPopupContextWindow(0, 1, false))
    {
        if(ImGui::BeginMenu("Physics"))
        {
            if(entity.noneOf<Rigidbody>() && ImGui::MenuItem("Rigidbody"))
            {
                entity.add<Rigidbody>();
                ImGui::CloseCurrentPopup();
            }
            ImGui::MenuItem("BoxCollider");
            ImGui::MenuItem("CircleCollider");
            ImGui::EndMenu();
        }
        if(ImGui::BeginMenu("Rendering"))
        {
            if(entity.noneOf<Model>() && ImGui::MenuItem("Model"))
            {
                entity.add<Model>();
                ImGui::CloseCurrentPopup();
            }
            ImGui::MenuItem("Camera");
            ImGui::MenuItem("Skybox");
            ImGui::MenuItem("Light");
            ImGui::MenuItem("Material");
            ImGui::EndMenu();
        }
        ImGui::EndPopup();
    }

    ImGui::End();
}

void Properties::showTag()
{
    constexpr size_t max_size = 256;
    if(entity.anyOf<Tag>())
    {
        auto& tag = entity.get<Tag>();

        char buf[max_size];
        memcpy(buf, tag.str.c_str(), tag.str.size() + 1);
        LEFT_LABEL(ImGui::InputText, "Tag", buf, max_size);
        tag.str = std::string(buf);
    }
    else
    {
        char buf[max_size] = {0};
        LEFT_LABEL(ImGui::InputText, "Tag", buf, max_size);
        if(strlen(buf))
            entity.add<Tag>(std::string(buf));
    }
}

void Properties::showTransform()
{
    if(entity.anyOf<Transform>())
    {
        if(ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
        {
            auto& tf = entity.get<Transform>();

            vectorEdit("Transform", tf.translation);
            vectorEdit("Rotation", tf.rotation);
            vectorEdit("Scale", tf.scale, 1.f);
        }
    }
}

void Properties::showRigidbody()
{
    if(entity.anyOf<Rigidbody>())
    {
        if(ImGui::CollapsingHeader("Rigidbody", ImGuiTreeNodeFlags_DefaultOpen))
        {
            auto& rb = entity.get<Rigidbody>();

            const char* items[]     = {"Dynamic", "Kinematic", "Static"};
            int         currentItem = static_cast<int>(rb.type);
            LEFT_LABEL(ImGui::Combo, "Type ", &currentItem, items, IM_ARRAYSIZE(items));
            rb.type = static_cast<Rigidbody::Type>(currentItem);

            LEFT_LABEL(ImGui::InputFloat, "Mass ", &rb.mass);

            ImGui::PushID("Force");
            ImGui::PushItemWidth(50);
            Vector2 force = rb.getForce();
            ImGui::Text("Force");
            ImGui::SameLine();
            LEFT_LABEL(ImGui::InputFloat, "x", &force.x);
            ImGui::SameLine();
            LEFT_LABEL(ImGui::InputFloat, "y", &force.y);
            rb.addForce(force - rb.getForce());
            ImGui::PopItemWidth();
            ImGui::PopID();
        }
    }
}

void Properties::showModel()
{
    if(entity.anyOf<Model>())
    {
        if(ImGui::CollapsingHeader("Model", ImGuiTreeNodeFlags_DefaultOpen))
        {
            auto& model = entity.get<Model>();
            if(model.getPath() == fs::path())
                ImGui::Text("Source  : (null)");
            else
                ImGui::Text("Source  : %s", model.getPath().string().c_str());
            if(ImGui::BeginDragDropTarget())
            {
                const auto payload = ImGui::AcceptDragDropPayload("browser_file");
                if(payload != nullptr)
                {
                    fs::path path((const wchar_t*)payload->Data);

                    // TODO: 添加组件已存在提示, UI 使用提示而不是断言
                    if(path.extension() == L".obj")
                        entity.get<Model>().load(Application::get().getAssetPath() / path);
                    else
                        Assert::isTrue(false);
                }
                ImGui::EndDragDropTarget();
            }

            if(model.getPath() == fs::path())
                return;

            ImGui::Text("Shapes  : %d", model.getMeshs().size());

            auto vertices = model.getVertexCount();
            if(vertices < 1000)
                ImGui::Text("Vertices: %d", vertices);
            else
                ImGui::Text("Vertices: %.1fk", (float)vertices / 1000);

            auto indices = model.getIndexCount();
            if(indices < 1000)
                ImGui::Text("Indices : %d", indices);
            else
                ImGui::Text("Indices : %.1fk", (float)indices / 1000);

            auto& meshs = model.getMeshs();
            auto& mats  = model.getMaterials();

            for(int i = 0; i < meshs.size(); i++)
            {
                if(ImGui::TreeNodeEx(std::format("Shape {}", i).c_str()))
                {
                    auto vertices = meshs[i].vertexArray->getVertexBuffer()->count();
                    if(vertices < 1000)
                        ImGui::Text("Vertices: %d", vertices);
                    else
                        ImGui::Text("Vertices: %.1fk", (float)vertices / 1000);

                    auto indices = meshs[i].vertexArray->getIndexBuffer()->count();
                    if(indices < 1000)
                        ImGui::Text("Indices : %d", indices);
                    else
                        ImGui::Text("Indices : %.1fk", (float)indices / 1000);

                    if(i < mats.size())
                    {
                        auto& mat = mats[i];

                        textureEdit("Albedo", mat.albedo);
                        textureEdit("Normal", mat.normal);
                        textureEdit("Metallic", mat.metallic);
                        textureEdit("Roughness", mat.roughness);
                        textureEdit("Emissive", mat.emissive);

                        ImGui::Separator();

                        colorEdit("Ambient", mat.ambient);
                        colorEdit("Diffuse", mat.diffuse);
                        colorEdit("Specular", mat.specular);
                        colorEdit("Emssion", mat.emission);
                    }
                    ImGui::TreePop();
                }
            }
        }
    }
}

void Properties::showLight()
{
}

void Properties::showMaterial()
{
    if(entity.anyOf<Material>())
    {
        if(ImGui::CollapsingHeader("Material", ImGuiTreeNodeFlags_DefaultOpen))
        {
            auto& material = entity.get<Material>();

            ImGui::Text("Shader   : Standard");
            ImGui::Text("Albedo   : ");
            ImGui::Text("Metallic : ");
            ImGui::Text("Shininess: %.3f", material.shininess);
        }
    }
}

void Properties::showSprite()
{
    if(entity.anyOf<Sprite>())
    {
        if(ImGui::CollapsingHeader("Sprite", ImGuiTreeNodeFlags_DefaultOpen))
        {
            ;
        }
    }
}

void Properties::showScript()
{
    if(entity.anyOf<Script>())
    {
        if(ImGui::CollapsingHeader("Script", ImGuiTreeNodeFlags_DefaultOpen))
        {
            ;
        }
    }
}

void Properties::textureEdit(const std::string& label, std::shared_ptr<Texture2D> texture)
{
    if(texture)
    {
        ImGui::Columns(2);

        ImGui::SetColumnWidth(0, 80.f);
        ImGui::Text(label.c_str());
        ImGui::NextColumn();

        ImGui::Image((ImTextureID)texture->getHandle(), {16, 16}, {1, 0}, {0, 1});
        if(ImGui::IsItemHovered())
            ImGui::Image((ImTextureID)texture->getHandle(), {64, 64}, {1, 0}, {0, 1});
        ImGui::Columns(1);
    }
}

void Properties::vectorEdit(const std::string& label, Vector3& value, float defaultValue)
{
    {
        struct buttonStyle
        {
            ImVec4 normal, hovered, active;
        };

        buttonStyle styles[] = {
            {{0.8f, 0.1f, 0.15f, 1.f}, {0.9f, 0.2f, 0.2f, 1.f}, {0.8f, 0.1f, 0.15f, 1.f}},    // red
            {{0.2f, 0.7f, 0.2f, 1.f}, {0.3f, 0.8f, 0.3f, 1.f}, {0.2f, 0.7f, 0.2f, 1.f}},      // green
            {{0.1f, 0.25f, 0.8f, 1.0f}, {0.2f, 0.35f, 0.9f, 1.0f}, {0.1f, 0.25f, 0.8f, 1.0f}} // blue
        };

        const char* strs[] = {"X", "Y", "Z"};

        auto   bold       = ImGui::GetIO().Fonts->Fonts[0];
        float  fontHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.f;
        ImVec2 size(fontHeight + 3.f, fontHeight);

        ImGui::PushID(label.c_str());

        ImGui::Columns(2);
        ImGui::SetColumnWidth(0, 80.f);
        ImGui::Text(label.c_str());
        ImGui::NextColumn();

        for(int i = 0; i < 3; i++)
        {
            ImGui::PushFont(bold);
            ImGui::PushStyleColor(ImGuiCol_Button, styles[i].normal);
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, styles[i].hovered);
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, styles[i].active);
            if(ImGui::Button(strs[i], size))
                value[i] = defaultValue;
            ImGui::PopStyleColor(3);
            ImGui::PopFont();
            ImGui::SameLine();
            ImGui::PushItemWidth(50);
            ImGui::DragFloat((std::string("##") + std::to_string(i)).c_str(), &value[i], 0.1f, 0.f, 0.f, "%.2f");
            ImGui::PopItemWidth();
            ImGui::SameLine();
        }
        ImGui::NewLine();

        ImGui::Columns(1);

        ImGui::PopID();
    }
}

void Properties::colorEdit(const std::string& label, Vector3& value)
{
    ImGui::PushID(label.c_str());
    ImGui::Columns(2);
    ImGui::SetColumnWidth(0, 80.f);
    ImGui::Text(label.c_str());
    ImGui::NextColumn();
    LEFT_LABEL(ImGui::ColorEdit3, "", (float*)&value);
    ImGui::Columns(1);
    ImGui::PopID();
}

} // namespace clem::ui