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
static Model  model;

GlfwWindow::GlfwWindow(const std::string& title, Size2i size)
{
    PROFILE_FUNC();

    handle = glfwCreateWindow(size.x, size.y, title.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(handle);

    auto success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    Assert::isTrue(success, "can't load OpenGL API");

    glfwSetWindowUserPointer(handle, static_cast<void*>(this));

    glfwSetErrorCallback([](int error, const char* desc) {
    });

    glfwSetWindowSizeCallback(handle, [](GLFWwindow* native, int width, int height) {
        auto win = static_cast<GlfwWindow*>(glfwGetWindowUserPointer(native));
        glViewport(0, 0, width, height);
        if(win->onResize)
            win->onResize({width, height});
    });

    glfwSetWindowCloseCallback(handle, [](GLFWwindow* native) {
        auto win = static_cast<GlfwWindow*>(glfwGetWindowUserPointer(native));
        if(win->onClose)
            win->onClose();
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

        uniform mat4 u_View;
        uniform mat4 u_Projection;

        out vec3 v_Position;
        out vec3 v_Color;

		void main()
		{
            v_Position  = a_Position;
            v_Color     = a_Color;
			gl_Position = u_Projection * u_View * vec4(a_Position, 1.0);
		}
	)",
                            R"(
		#version 450 core

		layout(location = 0) out vec4 color;

        in vec3 v_Position;
        in vec3 v_Color;

		void main()
		{
			color = vec4(v_Position + 0.5, 0.0);
            // color = vec4(v_Color, 0.0);
		}
	)");

    // cube.obj, cone.obj, sphere.obj
    model.load("../assets/models/cube.obj");

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

    auto renderer = Renderer::get();
    auto size     = getSize();

    glClearColor(30.f / 255, 144.f / 255, 255.f / 255, 1.f); // 湖蓝色
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    static Camera camera;
    camera.projection = Matrix4::createOrthographicOffCenter(-(float)size.x / (float)size.y, (float)size.x / (float)size.y, -1.f, 1.f, -1, 1);
    camera.view.rotateY(radians(1));
    camera.view.rotateX(radians(1));
    camera.view.rotateZ(radians(1));

    shader->uploadUniform("u_View", camera.view);
    shader->uploadUniform("u_Projection", camera.projection);

    renderer->submit(model.vertexArray, shader);

    // renderer->submit(vertexArray, shader);

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