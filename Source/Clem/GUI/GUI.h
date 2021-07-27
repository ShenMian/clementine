// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "DevelopMenu.h"
#include "Inspector.h"
#include "Layer.h"

#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/imgui.h>

namespace clem
{

class GUI
{
public:
	static void init()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui::StyleColorsDark();
	}

	static void deinit()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}
};

} // namespace clem