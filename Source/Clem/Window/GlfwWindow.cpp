// Copyright 2021 SMS
// License(Apache-2.0)

#include "GlfwWindow.h"
#include "Clem/Events/Events.h"
#include "Clem/Platform.h"
#include "Clem/Profiler.h"
#include "Clem/Rendering/Rendering.h"
#include "Clem/UI/UI.h"
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

	ImGui_ImplGlfw_InitForOpenGL(handle, true);
	ImGui_ImplOpenGL3_Init("#version 410");

	shader = Shader::create(R"(
		#version 410

		layout(location = 0) in vec3 a_Position;

		uniform mat4 u_ViewProjection;

		void main()
		{
			gl_Position = vec4(a_Position, 1.0) * u_ViewProjection;
		}
	)",
													R"(
		#version 410

		layout(location = 0) out vec4 color;

		void main()
		{
		}
	)");

	glCreateVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);

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

	vertexBuffer = VertexBuffer::create(&vertices, sizeof(vertices));
	indexBuffer  = IndexBuffer::create(&indices, sizeof(indices));

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

	assert(glGetError() == GL_NO_ERROR);
}

GlfwWindow::~GlfwWindow()
{
	PROFILE_FUNC();

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
	shader->uploadUniform("u_ViewProjection", camera.getViewProjection());

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

bool GlfwWindow::isVisible()
{
	return glfwGetWindowAttrib(handle, GLFW_VISIBLE);
}

void GlfwWindow::init()
{
	PROFILE_FUNC();

	auto success = glfwInit();
	assert(success);

	UI::init();
}

void GlfwWindow::deinit()
{
	PROFILE_FUNC();

	UI::deinit();

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