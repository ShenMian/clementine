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
#include <string>

namespace clem
{

class Inspector : public Layer
{
public:
	inline void update(Time dt) override
	{
		if(visible)
		{
			ImGui::Begin("Inspector", &visible);

			if(!entity.valid())
			{
				ImGui::Text("The entity is not valid");
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
			if(ImGui::CollapsingHeader("Transform"))
			{
				ImGui::PushItemWidth(50);
				auto& tf = entity.get<Transform>();

				auto& pos = tf.getPosition();
				ImGui::PushID("Position");
				ImGui::Text("Position");
				ImGui::SameLine();
				LEFT_LABEL(ImGui::InputFloat, "x", &pos.x);
				ImGui::SameLine();
				LEFT_LABEL(ImGui::InputFloat, "y", &pos.y);
				ImGui::PopID();

				ImGui::PushID("Rotation");
				ImGui::Text("Rotation");
				ImGui::SameLine();
				LEFT_LABEL(ImGui::InputFloat, "x", &tf.rotation.x);
				ImGui::SameLine();
				LEFT_LABEL(ImGui::InputFloat, "y", &tf.rotation.y);
				ImGui::PopID();

				ImGui::PushID("Scale");
				ImGui::Text("Scale   ");
				ImGui::SameLine();
				LEFT_LABEL(ImGui::InputFloat, "x", &tf.scale.x);
				ImGui::SameLine();
				LEFT_LABEL(ImGui::InputFloat, "y", &tf.scale.y);
				ImGui::PopItemWidth();
				ImGui::PopID();
			}
		}
	}

	inline void rigidbody()
	{
		if(entity.anyOf<Rigidbody>())
		{
			if(ImGui::CollapsingHeader("Rigidbody"))
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
			if(ImGui::CollapsingHeader("Sprite"))
			{
			}
		}
	}

	inline void script()
	{
		if(entity.anyOf<Script>())
		{
			if(ImGui::CollapsingHeader("Script"))
			{
			}
		}
	}

	bool visible = true;
};

} // namespace clem