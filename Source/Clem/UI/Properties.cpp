// Copyright 2021 SMS
// License(Apache-2.0)

#include "Properties.h"
#include "Browser.h"
#include "Components/Components.h"
#include "Physics/Rigidbody.h"
#include "Rendering/Console/Sprite.h"
#include "Rendering/Material.h"
#include <filesystem>
#include <glad/glad.h>
#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
#include <string>

namespace fs = std::filesystem;

namespace ImGui
{

bool BufferingBar(const char* label, float value, const ImVec2& size_arg, const ImU32& bg_col, const ImU32& fg_col)
{
    ImGuiWindow* window = GetCurrentWindow();
    if(window->SkipItems)
        return false;

    ImGuiContext&     g     = *GImGui;
    const ImGuiStyle& style = g.Style;
    const ImGuiID     id    = window->GetID(label);

    ImVec2 pos  = window->DC.CursorPos;
    ImVec2 size = size_arg;
    size.x -= style.FramePadding.x * 2;

    const ImRect bb(pos, ImVec2(pos.x + size.x, pos.y + size.y));
    ItemSize(bb, style.FramePadding.y);
    if(!ItemAdd(bb, id))
        return false;

    // Render
    const float circleStart = size.x * 0.7f;
    const float circleEnd   = size.x;
    const float circleWidth = circleEnd - circleStart;

    window->DrawList->AddRectFilled(bb.Min, ImVec2(pos.x + circleStart, bb.Max.y), bg_col);
    window->DrawList->AddRectFilled(bb.Min, ImVec2(pos.x + circleStart * value, bb.Max.y), fg_col);

    const float t     = g.Time;
    const float r     = size.y / 2;
    const float speed = 1.5f;

    const float a = speed * 0;
    const float b = speed * 0.333f;
    const float c = speed * 0.666f;

    const float o1 = (circleWidth + r) * (t + a - speed * (int)((t + a) / speed)) / speed;
    const float o2 = (circleWidth + r) * (t + b - speed * (int)((t + b) / speed)) / speed;
    const float o3 = (circleWidth + r) * (t + c - speed * (int)((t + c) / speed)) / speed;

    window->DrawList->AddCircleFilled(ImVec2(pos.x + circleEnd - o1, bb.Min.y + r), r, bg_col);
    window->DrawList->AddCircleFilled(ImVec2(pos.x + circleEnd - o2, bb.Min.y + r), r, bg_col);
    window->DrawList->AddCircleFilled(ImVec2(pos.x + circleEnd - o3, bb.Min.y + r), r, bg_col);
}

} // namespace ImGui

namespace clem::ui
{

void Properties::update(Time dt)
{
    {
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
        showMesh();
        showMaterial();
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
                if(entity.noneOf<Mesh>() && ImGui::MenuItem("Mesh"))
                {
                    entity.add<Mesh>();
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

            VectorEdit("Transform", tf.translation);
            VectorEdit("Rotation", tf.rotation);
            VectorEdit("Scale", tf.scale, 1.f);
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

void Properties::showMesh()
{
    if(entity.anyOf<Mesh>())
    {
        if(ImGui::CollapsingHeader("Mesh", ImGuiTreeNodeFlags_DefaultOpen))
        {
            auto& model = entity.get<Mesh>();
            if(model.path == fs::path())
                ImGui::Text("Source  : (null)");
            else
                ImGui::Text("Source  : %s", model.path.string().c_str());
            if(ImGui::BeginDragDropTarget())
            {
                const auto payload = ImGui::AcceptDragDropPayload("browser_file");
                if(payload != nullptr)
                {
                    fs::path path((const wchar_t*)payload->Data);

                    // TODO: 添加组件已存在提示, UI 使用提示而不是断言
                    if(path.extension() == L".obj")
                        entity.get<Mesh>().load(Browser::assets / path);
                    else
                        Assert::isTrue(false);
                }
                ImGui::EndDragDropTarget();
            }

            if(model.path == fs::path())
                return;

            auto vertices = model.vertexArray->getVertexBuffer()[0]->count();
            ImGui::Text("Vertices: %d", vertices);
        }
    }
}

void Properties::showMaterial()
{
    if(entity.anyOf<Material>())
    {
        if(ImGui::CollapsingHeader("Material", ImGuiTreeNodeFlags_DefaultOpen))
        {
            auto& material = entity.get<Material>();

            ImGui::Text("Shader: Standard");

            ColorEdit("Ambient", material.ambient);
            ColorEdit("Diffuse", material.diffuse);
            ColorEdit("Specular", material.specular);
            ImGui::Text("Shininess: %.5f", material.shininess);
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

void Properties::VectorEdit(const std::string& label, Vector3& value, float defaultValue)
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

void Properties::ColorEdit(const std::string& label, Vector3& value)
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