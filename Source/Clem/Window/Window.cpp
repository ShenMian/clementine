// Copyright 2021 SMS
// License(Apache-2.0)

#include "Window.h"
#include "Clem/Events/Events.h"
#include "Clem/GUI/GUI.h"
#include "Clem/Platform.h"
#include <cassert>
#include <cstdio>
#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>

using std::string;

namespace clem
{

Window::Window(std::string title, Size2i size)
{
	handle = glfwCreateWindow(size.x, size.y, title.c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(handle);

	auto success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	assert(success);

	glViewport(0, 0, size.x, size.y);

	glfwSetWindowUserPointer(handle, static_cast<void*>(this));

	glfwSetErrorCallback([](int error, const char* desc) {
	});

	glfwSetWindowSizeCallback(handle, [](GLFWwindow* native, int width, int height) {
		auto win = static_cast<Window*>(glfwGetWindowUserPointer(native));
		if(win->onResize)
			win->onResize({width, height});
	});

	glfwSetWindowCloseCallback(handle, [](GLFWwindow* native) {
		auto win = static_cast<Window*>(glfwGetWindowUserPointer(native));
		if(win->onClose)
			win->onClose();
	});

	glfwSetKeyCallback(handle, [](GLFWwindow* native, int key, int scancode, int action, int mods) {
		auto& dispatcher = EventDispatcher::get();
		switch(action)
		{
		case GLFW_PRESS:
			dispatcher.dispatch(KeyPressEvent(key));
			break;

		case GLFW_RELEASE:
			dispatcher.dispatch(KeyReleaseEvent(key));
			break;

		case GLFW_REPEAT:
			dispatcher.dispatch(KeyRepeatEvent(key));
			break;
		}
		// EventDispatcher::get().dispatch(KeyEvent(key, action == GLFW_PRESS || action == GLFW_REPEAT, action == GLFW_REPEAT));
	});

	glfwSetMouseButtonCallback(handle, nullptr);

	ImGui_ImplGlfw_InitForOpenGL(handle, true);
	ImGui_ImplOpenGL3_Init("#version 410");
}

Window::~Window()
{
	glfwMakeContextCurrent(handle);
	glfwDestroyWindow(handle);
}

void Window::update(Time dt)
{
	renderGui(dt);
	glfwSwapBuffers(handle);
	glfwPollEvents();
}

void Window::setTitle(const string& title)
{
	glfwSetWindowTitle(handle, title.c_str());
}

void Window::setSize(Size2i size)
{
	glfwSetWindowSize(handle, size.x, size.y);
}

Size2i Window::getSize()
{
	Size2i size;
	glfwGetWindowSize(handle, &size.x, &size.y);
	return size;
}

void Window::setPosition(Size2i size)
{
	glfwSetWindowPos(handle, size.x, size.y);
}

Size2i Window::getPosition()
{
	Size2i size;
	glfwGetWindowPos(handle, &size.x, &size.y);
	return size;
}

void Window::setVisible(bool visible)
{
	if(visible)
		glfwShowWindow(handle);
	else
		glfwHideWindow(handle);
}

bool Window::isVisible()
{
	return glfwGetWindowAttrib(handle, GLFW_VISIBLE);
}

void Window::init()
{
	auto success = glfwInit();
	assert(success);

	GUI::init();
}

void Window::deinit()
{
	GUI::deinit();

	glfwTerminate();
}

void Window::renderGui(Time dt)
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	for(auto layer : layers)
		layer->update(dt);

	ImGui::Render();
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

} // namespace clem