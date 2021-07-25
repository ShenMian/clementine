// Copyright 2021 SMS
// License(Apache-2.0)

#include "Layer.h"

#include "Clem.h"
#include <glad/glad.h>
#include <imgui/imgui.h>

#pragma once

namespace clem
{

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
				// auto   fps = ImGui::GetIO().Framerate;
				auto   fps = Main::getFrameRate();
				ImVec4 color;
				if(fps < 30)
					color = {1, 0, 0, 1};
				else if(fps < 60)
					color = {1, 1, 0, 1};
				else
					color = {0, 1, 0, 1};
				// ImGui::TextColored(color, "%3u", fps);
				ImGui::SameLine();
				ImGui::Text("FPS, %2.1f ms/frame", 1000.0f / fps);

				static float fpsTarget;
				fpsTarget = Main::getRenderRate();
				ImGui::SliderFloat("FPS target", &fpsTarget, 30.0f, 144.0f, "%.1f");
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
				ImGui::Text("ID    Tag        Position");
				Main::registry.all([](const auto& e) {
					ImGui::Text("%-5d", e.id());
					ImGui::SameLine();
					if(e.anyOf<Tag>())
						ImGui::Text("%-10s", e.get<Tag>().str.c_str());
					else
						ImGui::Text("(null)    ");
					ImGui::SameLine();
					if(e.anyOf<Transform>())
						ImGui::Text("%-4.1f, %-4.1f", e.get<Transform>().getWorldPosition().x, e.get<Transform>().getWorldPosition().y);
					else
						ImGui::Text("(null)    ");
				});
				ImGui::EndMenu();
			}

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

			ImGui::End();
		}
	}

private:
	bool visible = true;
};

} // namespace clem
