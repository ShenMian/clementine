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

static Camera  camera;
static Vector3 moveSpeed;

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
        camera.view.scale(Vector3(1 + 0.1 * yOffset, 1 + 0.1 * yOffset, 1 + 0.1 * yOffset)); // TODO: 调试用
        if(win->onScroll)
            win->onScroll(xOffset, yOffset);
    });

    glfwSetKeyCallback(handle, [](GLFWwindow* native, int key, int scancode, int action, int mods) {
        auto& dispatcher = EventDispatcher::get();
        switch(action)
        {
        case GLFW_PRESS:
            switch(key)
            {
            case GLFW_KEY_W:
                moveSpeed = camera.view.forword().normalize();
                break;
            }
            break;

        case GLFW_RELEASE:
            moveSpeed = Vector3::zero;
            break;

        case GLFW_REPEAT:
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
        uniform mat4 u_Model;

        out vec3 v_Position;
        out vec3 v_Color;
        out vec3 v_Normal;
        out vec2 v_Uv;
        out vec3 v_cam_position;

		void main()
		{
            v_Position  = a_Position;
            v_Color     = a_Color;
            v_Normal    = a_Normal;
            v_Uv        = a_Uv;

            v_cam_position = vec3(u_ViewProjection[3][0], u_ViewProjection[3][1], u_ViewProjection[3][2]);

			gl_Position = u_ViewProjection * u_Model * vec4(a_Position, 1.0);
		}
	)",
                            R"(
		#version 450 core

        in vec3 v_Position;
        in vec3 v_Color;
        in vec3 v_Normal;
        in vec2 v_Uv;
        in vec3 v_cam_position;

        uniform sampler2D u_Texture;

        vec4 light()
        {
            vec3 light_direction  = vec3(0.0, 0.0, -1.0);
            vec3 to_cam_direction = normalize(v_cam_position - v_Position);

            // 全局光
            float ka            = 0.1;
            vec3  ia            = vec3(1.0, 1.0, 1.0);
            vec3  ambient_light = ka * ia;

            // 漫反射
            float kd                  = 0.7;
            vec3  id                  = vec3(1.0, 1.0, 1.0);
            float amont_diffuse_light = max(0.0, dot(light_direction, v_Normal));
            vec3  diffuse_light       = kd * amont_diffuse_light * id;

            // 镜面反射
            float ks                    = 0.0;
            vec3  is                    = vec3(1.0, 1.0, 1.0);
            vec3  reflected_light       = reflect(light_direction, v_Normal);
            float shininess             = 30.0;
            float amount_specular_light = pow(max(0.0, dot(reflected_light, to_cam_direction)), shininess);
            vec3  specular_light        = ks * amount_specular_light * is;
            
            return vec4(ambient_light + diffuse_light + specular_light, 1.0);
        }

		void main()
		{
			// gl_FragColor = vec4(v_Uv, 0.0, 1.0) + light();
            // gl_FragColor = texture(u_Texture, v_Uv);
            gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0) + light();
		}
	)");

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

    camera.setPerspective(radians(50), size.x / size.y, 0.1f, 50.f);
    // Vector3 scale = Vector3::unit * 50;
    // camera.setOrthographic(-(float)size.x / (float)size.y * scale.y, (float)size.x / (float)size.y * scale.y, -scale.x, scale.x, -scale.z, scale.z);

    camera.view.setTranslation({0, 0, 20});

    camera.view.translate(moveSpeed);

    camera.view.rotateY(radians(1));
    // camera.view.rotateX(radians(0.5));
    // camera.view.rotateZ(radians(1));

    shader->uploadUniform("u_Texture", 0);
    shader->uploadUniform("u_ViewProjection", camera.getViewMatrix() * camera.getProjectionMatrix());

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