// Copyright 2021 SMS
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

		tag();
		transform();
		rigidbody();
		sprite();
		script();

		ImGui::End();
	}

	inline static Entity entity;

private:
	inline void tag()
	{
		if(entity.anyOf<Tag>())
		{
			auto& tag = entity.get<Tag>();

			char buf[20];
			strcpy_s(buf, 20, tag.str.c_str());
			LEFT_LABEL(ImGui::InputText, "Tag", buf, 20);
			tag.str = std::string(buf);
		}
		else
			LEFT_LABEL(ImGui::InputText, "Tag", "(null)", 6, ImGuiInputTextFlags_ReadOnly);
	}

	inline void transform()
	{
		if(entity.anyOf<Transform>())
		{
			if(ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
			{
				ImGui::PushItemWidth(50);
				auto& tf = entity.get<Transform>();

				auto& pos = tf.getPosition();
				Vector2Edit("Transform", pos);
				tf.setPosition(pos);

				Vector2Edit("Rotation", tf.rotation);
				Vector2Edit("Scale", tf.scale);

				/*
				ImGui::PushID("0");
				ImGui::Text("Position");
				ImGui::SameLine();
				LEFT_LABEL(ImGui::InputFloat, "x", &pos.x);
				ImGui::SameLine();
				LEFT_LABEL(ImGui::InputFloat, "y", &pos.y);
				ImGui::PopID();

				ImGui::PushID("1");
				ImGui::Text("Rotation");
				ImGui::SameLine();
				LEFT_LABEL(ImGui::InputFloat, "x", &tf.rotation.x);
				ImGui::SameLine();
				LEFT_LABEL(ImGui::InputFloat, "y", &tf.rotation.y);
				ImGui::PopID();

				ImGui::PushID("2");
				ImGui::Text("Scale   ");
				ImGui::SameLine();
				LEFT_LABEL(ImGui::InputFloat, "x", &tf.scale.x);
				ImGui::SameLine();
				LEFT_LABEL(ImGui::InputFloat, "y", &tf.scale.y);
				ImGui::PopItemWidth();
				ImGui::PopID();
				*/
			}
		}
	}

	inline void rigidbody()
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

	inline void sprite()
	{
		if(entity.anyOf<Sprite>())
		{
			if(ImGui::CollapsingHeader("Sprite", ImGuiTreeNodeFlags_DefaultOpen))
			{
			}
		}
	}

	inline void script()
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