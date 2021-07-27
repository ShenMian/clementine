// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Properties.h"
#include "Layer.h"
#include <glad/glad.h>
#include <imgui/imgui.h>

namespace clem::ui
{

class Hierarchy : public Layer
{
public:
  void update(Time dt) override
	{
		if(visible)
		{
			ImGui::Begin("Hierarchy", &visible);
			if(ImGui::CollapsingHeader("Entities"))
			{
				Main::registry.all([](const auto& e) {
					ImGui::Text("%-5d", e.id());
					ImGui::SameLine();
					if(e.anyOf<Tag>())
						ImGui::Text("%-10s", e.get<Tag>().str.c_str());
					else
						ImGui::Text("(null)    ");
					ImGui::SameLine();
					if(ImGui::Button((std::string("Properties##") + std::to_string(e.id())).c_str()))
						Properties::entity = e;
				});
			}
			ImGui::End();
		}
	}

private:
	bool visible = true;
};

} // namespace clem::ui