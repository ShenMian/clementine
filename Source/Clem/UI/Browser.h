// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Layer.h"
#include <glad/glad.h>
#include <imgui/imgui.h>
#include <filesystem>

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
				ImGui::Button(filename.c_str());
		}

		ImGui::End();
	}

private:
	fs::path assets  = "assets";
	fs::path current = "assets";

	bool visible = true;
};

} // namespace clem::ui
