// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Browser.h"
#include "Hierarchy.h"
#include "Properties.h"
#include "Setting.h"

#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/imgui.h>

namespace clem
{

class UI
{
public:
	static void init()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui::StyleColorsDark();
		auto& io = ImGui::GetIO();

		// io.Fonts->AddFontFromFileTTF("../Assets/Fonts/open_sans/OpenSans-Bold.ttf", 18.0f);
		// io.FontDefault = io.Fonts->AddFontFromFileTTF("../Assets/Fonts/open_sans/OpenSans-Regular.ttf", 18.0f);
	}

	static void deinit()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}
};

} // namespace clem