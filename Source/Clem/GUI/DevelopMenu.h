// Copyright 2021 SMS
// License(Apache-2.0)

#include "Layer.h"

#include "Clem/Components/Tag.h"
#include "Clem/Components/Transform.h"
#include "Clem/Physics/Rigidbody.h"

#include <glad/glad.h>
#include <imgui/imgui.h>

#pragma once

#define LEFT_LABEL(func, label, ...) (ImGui::TextUnformatted(label), ImGui::SameLine(), func("##" label, __VA_ARGS__))

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

			ImGui::End();
		}
	}

	inline static Entity entity;

private:
	bool visible = true;
};

class DevelopMenu : public Layer
{
public:
	inline void update(Time dt) override
	{
		if(visible)
		{
			ImGui::Begin("Dev Menu", &visible);

			if(ImGui::BeginMenu("Rendering"))
			{
				ImVec4 red(1, 0, 0, 1), yellow(1, 1, 0, 1), green(0, 1, 0, 1);
				auto   fps = Main::getFrameRate();
				ImVec4 color;
				if(fps < 30)
					color = red;
				else if(fps < 60)
					color = yellow;
				else
					color = green;
				ImGui::TextColored(color, "%3u", fps);
				ImGui::SameLine();
				ImGui::Text("FPS, %4.1f ms/frame", 1000.0f / fps);

				static float fpsTarget;
				fpsTarget = Main::getRenderRate();
				ImGui::PushItemWidth(70);
				LEFT_LABEL(ImGui::SliderFloat, "FPS target", &fpsTarget, 30.0f, 144.0f, "%.1f");
				ImGui::PopItemWidth();
				Main::setRenderRate((uint16_t)std::round(fpsTarget));
				Main::setInputRate((uint16_t)std::round(fpsTarget));
				Main::setUpdateRate((uint16_t)std::round(fpsTarget));

				if(ImGui::BeginMenu("OpenGL info"))
				{
					ImGui::Text("Version : %s", glGetString(GL_VERSION));
					ImGui::Text("Renderer: %s", glGetString(GL_RENDERER));
					ImGui::Text("Vendor  : %s", glGetString(GL_VENDOR));
					ImGui::EndMenu();
				}
				ImGui::EndMenu();
			}

			if(ImGui::BeginMenu("Entities"))
			{
				/*
				Main::registry.all([](const auto& e) {
					if(e.noneOf<Tag>())
						return;

					auto& tag = e.get<Tag>();
					ImGui::BeginMenu(tag.str.c_str());
					ImGui::EndMenu();
				});
				*/

				ImGui::Text("ID    Tag        ");
				Main::registry.all([](const auto& e) {
					ImGui::Text("%-5d", e.id());
					ImGui::SameLine();
					if(e.anyOf<Tag>())
						ImGui::Text("%-10s", e.get<Tag>().str.c_str());
					else
						ImGui::Text("(null)    ");
					ImGui::SameLine();
					if(ImGui::Button((std::string("Inspect") + std::to_string(e.id())).c_str()))
						Inspector::entity = e;
				});
				ImGui::EndMenu();
			}

			/*
			if(ImGui::BeginMenu("Profile"))
			{
				if(ImGui::MenuItem("Start", "Start profiling"))
				{
				}
				if(ImGui::MenuItem("Stop", "Stop profiling"))
				{
				}
				ImGui::EndMenu();
			}
			*/

			ImGui::End();
		}
	}

private:
	bool visible = true;
};

} // namespace clem
