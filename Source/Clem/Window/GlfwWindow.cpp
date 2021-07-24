// Copyright 2021 SMS
// License(Apache-2.0)

#include "GlfwWindow.h"
#include "Clem/Events/Events.h"
#include "Clem/GUI/GUI.h"
#include "Clem/Platform.h"
#include "Clem/Profiler.h"
#include "Clem/Rendering/OpenGL/OpenGLShader.h"
#include <cassert>
#include <cstdio>
#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/imgui.h>

using std::string;

namespace clem
{

static unsigned int vertexArray, vertexBuffer, indexBuffer;

GlfwWindow::GlfwWindow(const std::string& title, Size2i size)
{
	PROFILE_FUNC();

	handle = glfwCreateWindow(size.x, size.y, title.c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(handle);

	auto success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	assert(success);

	glViewport(0, 0, size.x, size.y);

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

	std::string vertexSrc = R"(
		#version 410

		layout(location = 0) in vec3 a_Position;

		void main()
		{
			gl_Position = vec4(a_Position, 1.0);
		}
	)";
	std::string fregmentSrc = R"(
		#version 410

		layout(location = 0) out vec4 color;

		void main()
		{
		}
	)";

	shader = std::make_unique<OpenGLShader>(vertexSrc, fregmentSrc);

	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

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

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

	unsigned int indices[3] = {0, 1, 2};
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);
}

GlfwWindow::~GlfwWindow()
{
	glfwMakeContextCurrent(handle);
	glfwDestroyWindow(handle);
}

void GlfwWindow::update(Time dt)
{
	PROFILE_FUNC();

	glClearColor(30.0f / 255, 144.0f / 255, 255.0f / 255, 1.0f); // 湖蓝色
	glClear(GL_COLOR_BUFFER_BIT);
	// shader->bind();

	glBindVertexArray(vertexArray);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

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

bool GlfwWindow::isVisible()
{
	return glfwGetWindowAttrib(handle, GLFW_VISIBLE);
}

void GlfwWindow::init()
{
	auto success = glfwInit();
	assert(success);

	GUI::init();
}

void GlfwWindow::deinit()
{
	GUI::deinit();

	glfwTerminate();
}

void GlfwWindow::renderGui(Time dt)
{
	PROFILE_FUNC();

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	for(auto layer : layers)
		layer->update(dt);

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

} // namespace clem