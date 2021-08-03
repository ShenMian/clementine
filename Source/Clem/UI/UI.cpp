// Copyright 2021 SMS
// License(Apache-2.0)

#include "UI.h"

#include "Clem/Rendering/Renderer.h"
#include "Clem/Window/WindowBase.h"

#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/backends/imgui_impl_vulkan.h>
#include <imgui/imgui.h>

namespace clem
{

void UI::init(WindowBase* window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	auto& io = ImGui::GetIO();

	// 自定义字体
	// io.Fonts->AddFontFromFileTTF("../Assets/Fonts/open_sans/OpenSans-Bold.ttf", 18.0f);
	// io.FontDefault = io.Fonts->AddFontFromFileTTF("../Assets/Fonts/open_sans/OpenSans-Regular.ttf", 18.0f);

	switch(Renderer::getAPI())
	{
		using enum Renderer::API;
	case OpenGL:
		ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)window->nativeHandle(), true);
		ImGui_ImplOpenGL3_Init("#version 410");
		break;

	case Vulkan:
		ImGui_ImplGlfw_InitForVulkan((GLFWwindow*)window->nativeHandle(), true);
		// ImGui_ImplVulkan_Init(); // FIXME
		break;
	}
}

void UI::deinit()
{
	switch(Renderer::getAPI())
	{
		using enum Renderer::API;
	case OpenGL:
		ImGui_ImplOpenGL3_Shutdown();
		break;

	case Vulkan:
		ImGui_ImplVulkan_Shutdown();
		break;
	}

	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

} // namespace clem