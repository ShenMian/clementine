﻿// Copyright 2021 SMS
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
#include <vulkan/vulkan.hpp>

#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/backends/imgui_impl_vulkan.h>
#include <imgui/imgui.h>

using std::string;

namespace clem
{

static unsigned int vertexArray;

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

    glViewport(0, 0, size.x, size.y);

    shader = Shader::create(R"(
		#version 410

		layout(location = 0) in vec3 a_Position;

		void main()
		{
			gl_Position = vec4(1.0) * vec4(a_Position, 1.0);
		}
	)",
                            R"(
		#version 410

		layout(location = 0) out vec4 color;

		void main()
		{
			color = vec4(0.0, 1.0, 0.0, 0.0);
		}
	)");

    float vertices[3 * 3] = {
        -0.5f,
        -0.5f,
        0.0f,

        0.5f,
        -0.5f,
        0.0f,

        0.0f,
        0.5f,
        0.0f,
    };
    unsigned int indices[3] = {0, 1, 2};

    glCreateVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);

    vertexBuffer = VertexBuffer::create(&vertices, sizeof(vertices));
    indexBuffer  = IndexBuffer::create(&indices, sizeof(indices));

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

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

    glClearColor(30.0f / 255, 144.0f / 255, 255.0f / 255, 1.0f); // 湖蓝色
    glClear(GL_COLOR_BUFFER_BIT);

    static Camera camera;

    shader->bind();
    // shader->uploadUniform("u_ViewProjection", camera.getViewProjection());

    glBindVertexArray(vertexArray);

    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

    assert(glGetError() == GL_NO_ERROR);

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

Size2i GlfwWindow::getSize()
{
    Size2i size;
    glfwGetWindowSize(handle, &size.x, &size.y);
    return size;
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