// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Clem/Components/Tag.h"
#include "Inspector.h"
#include "Layer.h"
#include <array>
#include <glad/glad.h>
#include <imgui/imgui.h>
#include <numeric>

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
				ImVec4 red(1, 0, 0, 1), yellow(1, 1, 0, 1), green(0, 1, 0, 1);
				auto   fps = Main::getFrameRate();

				static std::array<float, 120> fpsArray;
				static int                    i = 0;
				if(i < 120)
					fpsArray[i++] = 1000.0f / dt.milliseconds();
				else
					i = 0;
				// auto fps = std::accumulate(fpsArray.begin(), fpsArray.end(), 0) / fpsArray.size();
				LEFT_LABEL(ImGui::PlotLines, "FPS", fpsArray.data(), (int)fpsArray.size());

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
				ImGui::Text("ID    Tag        ");
				Main::registry.all([](const auto& e) {
					ImGui::Text("%-5d", e.id());
					ImGui::SameLine();
					if(e.anyOf<Tag>())
						ImGui::Text("%-10s", e.get<Tag>().str.c_str());
					else
						ImGui::Text("(null)    ");
					ImGui::SameLine();
					if(ImGui::Button((std::string("Inspect##") + std::to_string(e.id())).c_str()))
						Inspector::entity = e;
				});
				ImGui::EndMenu();
			}

			ImGui::End();
		}
	}

private:
	bool visible = true;
};

} // namespace clem