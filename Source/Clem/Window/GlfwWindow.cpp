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

static Vector3 move;

GlfwWindow::GlfwWindow(const std::string& title, Size2i size)
{
    PROFILE_FUNC();

    auto       monitor   = glfwGetPrimaryMonitor();
    const auto videoMode = glfwGetVideoMode(monitor);

    bool fullscreen = false;
    if(fullscreen)
        handle = glfwCreateWindow(videoMode->width, videoMode->height, title.c_str(), monitor, nullptr);
    else
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
        win->camera.view.scale(Vector3(1 - 0.1 * yOffset, 1 - 0.1 * yOffset, 1 - 0.1 * yOffset)); // TODO: 调试用
        if(win->onScroll)
            win->onScroll(xOffset, yOffset);
    });

    glfwSetKeyCallback(handle, [](GLFWwindow* native, int key, int scancode, int action, int mods) {
        const auto win = static_cast<GlfwWindow*>(glfwGetWindowUserPointer(native));
        switch(action)
        {
        case GLFW_PRESS:
            switch(key)
            {
            case GLFW_KEY_ESCAPE:
                win->onClose();
                break;

            case GLFW_KEY_W:
                move = win->camera.view.getInversed().forword().normalize() * 0.1;
                break;

            case GLFW_KEY_S:
                move = win->camera.view.getInversed().back().normalize() * 0.1;
                break;

            case GLFW_KEY_A:
                move = win->camera.view.getInversed().left().normalize() * 0.1;
                break;

            case GLFW_KEY_D:
                move = win->camera.view.getInversed().right().normalize() * 0.1;
                break;

            case GLFW_KEY_LEFT_SHIFT:
                move = win->camera.view.getInversed().up().normalize() * 0.1;
                break;

            case GLFW_KEY_SPACE:
                move = win->camera.view.getInversed().down().normalize() * 0.1;
                break;
            }
            break;

        case GLFW_RELEASE:
            move = Vector3::zero;
            break;

        case GLFW_REPEAT:
            break;
        }
        // EventDispatcher::get().dispatch(KeyEvent(key, action == GLFW_PRESS || action == GLFW_REPEAT, action == GLFW_REPEAT));
    });

    glfwSetCursorPosCallback(handle, [](GLFWwindow* native, double x, double y) {
        const auto    win   = static_cast<GlfwWindow*>(glfwGetWindowUserPointer(native));
        /*
        static double lastX = 0.f, lastY = 0.f;
        float         ix = 0.001, iy = 0.001;
        win->camera.view.rotateY(-ix * (x - lastX));
        win->camera.view.rotateX(-iy * (y - lastY));
        lastX = x, lastY = y;
        */
    });

    glfwSetMouseButtonCallback(handle, nullptr);

    // 开启 MASS 抗锯齿
    glfwWindowHint(GLFW_SAMPLES, 2);
    glEnable(GL_MULTISAMPLE);

    shader = Shader::create(R"(
		#version 330 core

		layout(location = 0) in vec3 a_position;
		layout(location = 1) in vec3 a_color;
		layout(location = 2) in vec3 a_normal;
		layout(location = 3) in vec2 a_uv;

        uniform mat4 u_view_projection;
        uniform mat4 u_view;
        uniform mat4 u_projection;
        uniform mat4 u_model;

        out vec3 v_position;
        out vec3 v_color;
        out vec3 v_normal;
        out vec2 v_uv;

        out vec3 v_cam_position;

		void main()
		{
            v_position  = mat3(u_model) * a_position;
            v_color     = a_color;
            v_normal    = normalize(mat3(u_model) * a_normal);
            v_uv        = a_uv;

            v_cam_position = vec3(-u_view_projection[3][0], -u_view_projection[3][1], -u_view_projection[3][2]);

			gl_Position = u_projection * inverse(u_view) * u_model * vec4(a_position, 1.0);
		}
	)",
                            R"(
		#version 330 core

        in vec3 v_position;
        in vec3 v_color;
        in vec3 v_normal;
        in vec2 v_uv;

        in vec3 v_cam_position;

        uniform sampler2D u_texture;

        vec4 light()
        {
            vec3 light_direction = normalize(vec3(0.0, 0.0, 1.0));

            vec3 direction_to_light = -light_direction;
            vec3 direction_to_cam   = normalize(v_position - v_cam_position);

            // 全局光
            const float ka            = 0.1;
            const vec3  ia            = vec3(1.0, 1.0, 1.0);
            vec3        ambient_light = ka * ia;

            // 漫反射
            const float kd                  = 0.7;
            const vec3  id                  = vec3(1.0, 1.0, 1.0);
            float       amont_diffuse_light = max(0.0, dot(-direction_to_light, v_normal));
            vec3        diffuse_light       = kd * amont_diffuse_light * id;

            // 镜面反射
            const float ks                    = 0.7;
            const vec3  is                    = vec3(1.0, 1.0, 1.0);
            vec3        reflected_light       = reflect(direction_to_light, v_normal);
            float       shininess             = 30.0;
            float       amount_specular_light = pow(max(0.0, dot(reflected_light, direction_to_cam)), shininess);
            vec3        specular_light        = ks * amount_specular_light * is;

            return vec4(ambient_light + diffuse_light + specular_light, 1.0);
        }

		void main()
		{
            // gl_FragColor = texture(u_texture, v_uv);
			// gl_FragColor = vec4(v_uv, 0.0, 1.0);
            gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0) * light();
		}
	)");

#if 1
    camera.setPerspective(radians(50), (float)size.x / (float)size.y, 0.1f, 100.f);
#else
    camera.setOrthographic((float)size.x / 20, (float)size.y / 20, -100, 100);
    // camera.view.rotateZ(radians(180));
#endif
    camera.setDirection({0, 0, -20}, {0, 0, -1});
    camera.view.setTranslation({0, 0, -20});

    // static auto texture = Texture2D::create("../assets/textures/SMS.png");
    // texture->bind();

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

    renderer->beginFrame();

    // FIXME: Camera::view 被不断改变

    camera.view.translate(move);

    // camera.view.rotateY(radians(1));
    // camera.view.rotateX(radians(0.5));
    // camera.view.rotateZ(radians(1));

    shader->uploadUniform("u_Texture", 0);
    shader->uploadUniform("u_view", camera.getViewMatrix());
    shader->uploadUniform("u_projection", camera.getProjectionMatrix());
    shader->uploadUniform("u_view_projection", camera.getViewProjectionMatrix());

    Main::registry.each<Model>([&](const Entity& e) {
        auto& model = e.get<Model>();
        auto& tf    = e.get<Transform>();
        renderer->submit(model.vertexArray, shader, tf.getModelMatrix());
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