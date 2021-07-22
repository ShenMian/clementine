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

	glfwSetWindowSizeCallback(handle, [](GLFWwindow* native, int width, int height) {
		auto win = static_cast<WindowsWindow*>(glfwGetWindowUserPointer(native));
		win->onResize(width, height);
	});

	glfwSetWindowCloseCallback(handle, [](GLFWwindow* native) {
		auto win = static_cast<WindowsWindow*>(glfwGetWindowUserPointer(native));
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
	glfwPollEvents();
}

void WindowsWindow::setTitle(const string& title)
{
	glfwSetWindowTitle(handle, title.c_str());
}

Size2i WindowsWindow::getVisibleSize()
{
	Size2i size;
	glfwGetWindowSize(handle, &size.x, &size.y);
	return size;
}

void WindowsWindow::init()
{
	glfwInit();
}

void WindowsWindow::deinit()
{
	glfwTerminate();
}

} // namespace clem