﻿// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Clem/Components/Script.h"
#include "Clem/Components/Tag.h"
#include "Clem/Components/Transform.h"
#include "Clem/Physics/Rigidbody.h"
#include "Clem/Rendering/Console/Sprite.h"
#include "Layer.h"
#include <glad/glad.h>
#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
#include <string>

namespace clem::ui
{

class Properties : public Layer
{
public:
	inline void update(Time dt) override
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
		showSprite();
		showScript();

		// 空白区域右键
		if(ImGui::BeginPopupContextWindow(0, 1, false))
		{
			if(ImGui::BeginMenu("Add component"))
			{
				if(entity.noneOf<Transform>() && ImGui::MenuItem("Transform"))
				{
					entity.add<Transform>();
					ImGui::CloseCurrentPopup();
				}
				if(entity.noneOf<Rigidbody>() && ImGui::MenuItem("Rigidbody"))
				{
					entity.add<Rigidbody>();
					ImGui::CloseCurrentPopup();
				}
				ImGui::EndMenu();
			}
			ImGui::EndPopup();
		}

		ImGui::End();
	}

	inline static Entity entity;

private:
	inline void showTag()
	{
		constexpr size_t max_size = 256;
		if(entity.anyOf<Tag>())
		{
			auto& tag = entity.get<Tag>();

			char buf[max_size];
			strcpy_s(buf, max_size, tag.str.c_str());
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

	inline void showTransform()
	{
		if(entity.anyOf<Transform>())
		{
			if(ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
			{
				ImGui::PushItemWidth(50);
				auto& tf = entity.get<Transform>();

				Vector2Edit("Transform", tf.translation);
				Vector2Edit("Rotation", tf.rotation);
				Vector2Edit("Scale", tf.scale);
			}
		}
	}

	inline void showRigidbody()
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

	inline void showSprite()
	{
		if(entity.anyOf<Sprite>())
		{
			if(ImGui::CollapsingHeader("Sprite", ImGuiTreeNodeFlags_DefaultOpen))
			{
			}
		}
	}

	inline void showScript()
	{
		if(entity.anyOf<Script>())
		{
			if(ImGui::CollapsingHeader("Script", ImGuiTreeNodeFlags_DefaultOpen))
			{
			}
		}
	}

	void Vector2Edit(const std::string& label, Vector2& value)
	{
		struct buttonStyle
		{
			ImVec4 normal, hovered, active;
		};

		buttonStyle styles[] = {
				{{0.8f, 0.1f, 0.15f, 1.0f}, {0.9f, 0.2f, 0.2f, 1.0f}, {0.8f, 0.1f, 0.15f, 1.0f}}, // red
				{{0.2f, 0.7f, 0.2f, 1.0f}, {0.3f, 0.8f, 0.3f, 1.0f}, {0.2f, 0.7f, 0.2f, 1.0f}}    // green
		};

		const char* strs[] = {"X", "Y"};

		auto   bold       = ImGui::GetIO().Fonts->Fonts[0];
		float  fontHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 size(fontHeight + 3.0f, fontHeight);

		ImGui::PushID(label.c_str());

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, 100.0f);
		ImGui::Text(label.c_str());
		ImGui::NextColumn();

		for(int i = 0; i < 2; i++)
		{
			ImGui::PushFont(bold);
			ImGui::PushStyleColor(ImGuiCol_Button, styles[i].normal);
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, styles[i].hovered);
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, styles[i].active);
			if(ImGui::Button(strs[i], size))
				value[i] = 0.0f;
			ImGui::PopStyleColor(3);
			ImGui::PopFont();
			ImGui::SameLine();
			ImGui::DragFloat((std::string("##") + std::to_string(i)).c_str(), &value[i], 0.1f, 0.0f, 0.0f, "%.2f");
			ImGui::SameLine();
		}
		ImGui::NewLine();

		ImGui::Columns(1);

		ImGui::PopID();
	}

	bool visible = true;
};

} // namespace clem::ui