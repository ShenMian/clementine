// Copyright 2021 SMS
// License(Apache-2.0)

#include "GlfwWindow.h"
#include "Events/Events.h"
#include "Platform.h"
#include "Profiler.h"
#include "Rendering/Rendering.h"
#include "UI/UI.h"
#include <cassert>
#include <cstdio>
#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/backends/imgui_impl_vulkan.h>
#include <imgui/imgui.h>

#include "Components/Components.h"

using std::string;

namespace clem
{

GlfwWindow::GlfwWindow(const std::string& title, Size2i size)
{
    PROFILE_FUNC();

    handle = glfwCreateWindow(size.x, size.y, title.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(handle);

    auto success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    Assert::isTrue(success, "can't load OpenGL API");

    glfwSetWindowUserPointer(handle, static_cast<void*>(this));

    glfwSetErrorCallback([](int error, const char* desc) {
        Assert::isTrue(false, desc);
    });

    glfwSetWindowSizeCallback(handle, [](GLFWwindow* native, int width, int height) {
        const auto win = static_cast<GlfwWindow*>(glfwGetWindowUserPointer(native));
        Renderer::get()->setViewport(0, 0, width, height);
        if(win->onResize)
            win->onResize({width, height});
    });

    glfwSetWindowCloseCallback(handle, [](GLFWwindow* native) {
        const auto win = static_cast<GlfwWindow*>(glfwGetWindowUserPointer(native));
        if(win->onClose)
            win->onClose();
    });

    glfwSetScrollCallback(handle, [](GLFWwindow* native, double xOffset, double yOffset) {
        const auto win = static_cast<GlfwWindow*>(glfwGetWindowUserPointer(native));
        if(win->onScroll)
            win->onScroll(xOffset, yOffset);
    });

    glfwSetKeyCallback(handle, [](GLFWwindow* native, int key, int scancode, int action, int mods) {
        auto& dispatcher = EventDispatcher::get();
        switch(action)
        {
        case GLFW_PRESS:
            // dispatcher.dispatch(KeyPressEvent(key));
            break;

        case GLFW_RELEASE:
            // dispatcher.dispatch(KeyReleaseEvent(key));
            break;

        case GLFW_REPEAT:
            // dispatcher.dispatch(KeyRepeatEvent(key));
            break;
        }
        // EventDispatcher::get().dispatch(KeyEvent(key, action == GLFW_PRESS || action == GLFW_REPEAT, action == GLFW_REPEAT));
    });

    glfwSetMouseButtonCallback(handle, nullptr);

    shader = Shader::create(R"(
		#version 450 core

		layout(location = 0) in vec3 a_Position;
		layout(location = 1) in vec3 a_Color;
		layout(location = 2) in vec3 a_Normal;
		layout(location = 3) in vec2 a_Uv;

        uniform mat4 u_ViewProjection;
        uniform mat4 u_Transform;

        out vec3 v_Position;
        out vec3 v_Color;
        out vec2 v_Uv;

		void main()
		{
            v_Position  = a_Position;
            v_Color     = a_Color;
            v_Uv        = a_Uv;

			gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
		}
	)",
                            R"(
		#version 450 core

		layout(location = 0) out vec4 color;

        in vec3 v_Position;
        in vec3 v_Color;
        in vec2 v_Uv;

		void main()
		{
			color = vec4(v_Uv, 0.0, 1.0);
            // color = vec4(v_Color, 0.0);
		}
	)");

    UI::init(this);

    Assert::isTrue(glGetError() == GL_NO_ERROR);
}

GlfwWindow::~GlfwWindow()
{
    PROFILE_FUNC();

    UI::deinit();
    glfwMakeContextCurrent(handle);
    glfwDestroyWindow(handle);
}

void GlfwWindow::update(Time dt)
{
    PROFILE_FUNC();

    static Camera camera;

    auto renderer = Renderer::get();
    auto size     = getSize();

    renderer->beginFrame();

    Vector3 scale = Vector3::unit * 5;
    camera.setPerspective(radians(50), size.x / size.y, 0.1f, 50.f);
    // camera.setOrthographic(-(float)size.x / (float)size.y * scale.y, (float)size.x / (float)size.y * scale.y, -scale.x, scale.x, -scale.z, scale.z);
    camera.view.setTranslation({0, 0, 20});

    camera.view.rotateY(radians(1));
    // camera.view.rotateX(radians(0.5));
    // camera.view.rotateZ(radians(1));

    shader->uploadUniform("u_ViewProjection", camera.getViewProjectionMatrix());

    Main::registry.each<Model>([&](const Entity& e) {
        auto& model = e.get<Model>();
        auto& tf    = e.get<Transform>();

        renderer->submit(model.vertexArray, shader, tf.transform);
    });

    renderer->endFrame();

    renderGui(dt);

    glfwSwapBuffers(handle);
    glfwPollEvents();
}

void GlfwWindow::setTitle(const string& title)
{
    glfwSetWindowTitle(handle, title.c_str());
}

void GlfwWindow::setSize(Size2i size)
{
    glfwSetWindowSize(handle, size.x, size.y);
}

Size2 GlfwWindow::getSize()
{
    int x, y;
    glfwGetWindowSize(handle, &x, &y);
    return {(float)x, (float)y};
}

void GlfwWindow::setPosition(Size2i size)
{
    glfwSetWindowPos(handle, size.x, size.y);
}

Size2i GlfwWindow::getPosition()
{
    Size2i size;
    glfwGetWindowPos(handle, &size.x, &size.y);
    return size;
}

void GlfwWindow::setVisible(bool visible)
{
    if(visible)
        glfwShowWindow(handle);
    else
        glfwHideWindow(handle);
}

bool GlfwWindow::isVisible() const
{
    return glfwGetWindowAttrib(handle, GLFW_VISIBLE);
}

void* GlfwWindow::nativeHandle() const
{
    return handle;
}

void GlfwWindow::init()
{
    PROFILE_FUNC();

    auto success = glfwInit();
    Assert::isTrue(success, "GLFW init failed");
}

void GlfwWindow::deinit()
{
    PROFILE_FUNC();
    glfwTerminate();
}

void GlfwWindow::renderGui(Time dt)
{
    PROFILE_FUNC();

    if(Renderer::getAPI() == Renderer::API::OpenGL)
        ImGui_ImplOpenGL3_NewFrame();
    else
        ImGui_ImplVulkan_NewFrame();
    ImGui_ImplGlfw_NewFrame();

    ImGui::NewFrame();

    for(auto layer : layers)
        layer->update(dt);

    ImGui::Render();

    if(Renderer::getAPI() == Renderer::API::OpenGL)
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    else
        ; // ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData());
}

/*
vk::SurfaceKHR GlfwWindow::getWindowSurface(const vk::Instance& vkInstance) const
{
	VkSurfaceKHR surface;
	auto ret = static_cast<vk::Result>(glfwCreateWindowSurface((VkInstance)vkInstance, handle, nullptr, &surface));
	return surface;
}
*/

} // namespace clem