// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Rendering/Rendering.h"
#include "Layer.h"
#include <filesystem>
#include <glad/glad.h>
#include <imgui/imgui.h>

namespace fs = std::filesystem;

namespace clem::ui
{

class Browser : public Layer
{
	void update(Time dt) override
	{
		if(!visible)
			return;

		ImGui::Begin("Browser", &visible);

		assert(fs::exists(assets));
		assert(fs::exists(current));

		if(current != assets)
		{
			if(ImGui::Button("<"))
				current = current.parent_path();
		}

		auto fileIcon = Texture2D::create("../Assets/SMS.png");
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4());
		ImGui::ImageButton(fileIcon->nativeHandle(), {40, 40}, {0, 1}, {1, 0});
		ImGui::PopStyleColor();
		for(const auto& entry : fs::directory_iterator(current))
		{
			// TODO: 使用 Texture2D 创建 ImageButton
			auto filename = entry.path().filename().string();
			if(entry.is_directory())
			{
				if(ImGui::Button(filename.c_str()))
					current = entry;
			}
			else
			{
				ImGui::Button(filename.c_str());
			}
		}

		ImGui::End();
	}

private:
	fs::path assets  = "assets";
	fs::path current = "assets";

	bool visible = true;
};

} // namespace clem::ui
