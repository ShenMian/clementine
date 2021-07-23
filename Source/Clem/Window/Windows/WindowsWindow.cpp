// Copyright 2021 SMS
// License(Apache-2.0)

#include "WindowsWindow.h"
#include "Clem/Events/Events.h"
#include "Clem/Platform.h"
#include <cassert>
#include <cstdio>

using std::string;

namespace clem
{

WindowsWindow::WindowsWindow(std::string title, Size2i size)
{
	handle = glfwCreateWindow(size.x, size.y, title.c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(handle);

	glfwSetWindowUserPointer(handle, static_cast<void*>(this));

	glfwSetErrorCallback([](int error, const char* desc) {
	});

	glfwSetWindowSizeCallback(handle, [](GLFWwindow* native, int width, int height) {
		auto win = static_cast<WindowsWindow*>(glfwGetWindowUserPointer(native));
		if(win->onResize)
			win->onResize({width, height});
	});

	glfwSetWindowCloseCallback(handle, [](GLFWwindow* native) {
		auto win = static_cast<WindowsWindow*>(glfwGetWindowUserPointer(native));
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
}

WindowsWindow::~WindowsWindow()
{
	glfwMakeContextCurrent(handle);
	glfwDestroyWindow(handle);
}

void WindowsWindow::update()
{
	glfwSwapBuffers(handle);
	glfwPollEvents();
}

void WindowsWindow::setTitle(const string& title)
{
	glfwSetWindowTitle(handle, title.c_str());
}

void WindowsWindow::setSize(Size2i size)
{
	glfwSetWindowSize(handle, size.x, size.y);
}

Size2i WindowsWindow::getSize()
{
	Size2i size;
	glfwGetWindowSize(handle, &size.x, &size.y);
	return size;
}

void WindowsWindow::setPosition(Size2i size)
{
	glfwSetWindowPos(handle, size.x, size.y);
}

Size2i WindowsWindow::getPosition()
{
	Size2i size;
	glfwGetWindowPos(handle, &size.x, &size.y);
	return size;
}

void WindowsWindow::setVisible(bool visible)
{
	if(visible)
		glfwShowWindow(handle);
	else
		glfwHideWindow(handle);
}

bool WindowsWindow::isVisible()
{
	return glfwGetWindowAttrib(handle, GLFW_VISIBLE);
}

void WindowsWindow::init()
{
	auto success = glfwInit();
	assert(success);
}

void WindowsWindow::deinit()
{
	glfwTerminate();
}

} // namespace clem