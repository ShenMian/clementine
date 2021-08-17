// Copyright 2021 SMS
// License(Apache-2.0)

#include "UI.h"

#include "Rendering/Renderer.h"
#include "Window/WindowBase.h"

#include <glfw/glfw3.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/backends/imgui_impl_vulkan.h>
#include <imgui/imgui.h>

namespace clem
{

void UI::beginFrame()
{
    if(Renderer::getAPI() == Renderer::API::OpenGL)
        ImGui_ImplOpenGL3_NewFrame();
    else
        ImGui_ImplVulkan_NewFrame();
    ImGui_ImplGlfw_NewFrame();

    ImGui::NewFrame();
}

void UI::endFrame()
{
    ImGui::Render();

    if(Renderer::getAPI() == Renderer::API::OpenGL)
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    else
        ; // ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData());

    if(ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        const auto context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(context);
    }
}

void UI::windowInit(WindowBase* win)
{
    switch(Renderer::getAPI())
    {
        using enum Renderer::API;

    case OpenGL:
        ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)win->nativeHandle(), true);
        ImGui_ImplOpenGL3_Init("#version 450");
        break;

    case Vulkan:
        ImGui_ImplGlfw_InitForVulkan((GLFWwindow*)win->nativeHandle(), true);
        // ImGui_ImplVulkan_Init(); // FIXME
        break;
    }
}

void UI::windowDeinit()
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
}

void UI::init()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    auto& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    // io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // 允许 UI 组件分离到窗口外, 称为新的窗口

    if(io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        ImGuiStyle& style                 = ImGui::GetStyle();
        style.WindowRounding              = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    // 自定义字体
    // io.Fonts->AddFontFromFileTTF("../assets/fonts/open_sans/OpenSans-Bold.ttf", 18.f);
    // io.FontDefault = io.Fonts->AddFontFromFileTTF("../assets/fonts/open_sans/OpenSans-Regular.ttf", 18.f);
}

void UI::deinit()
{
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

} // namespace clem