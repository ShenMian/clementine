// Copyright 2021 SMS
// License(Apache-2.0)

#include "Viewport.h"
#include "Browser.h"
#include "Rendering/OpenGL/GLFrameBuffer.h"
#include "Window/GlfwWindow.h"
#include <glad/glad.h>
#include <imgui/imgui.h>

#include <glfw/glfw3.h>

namespace clem::ui
{

void Viewport::update(Time dt)
{
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{0, 0});
    ImGui::Begin("Viewport", &visible);
    ImVec2 viewportPos = {ImGui::GetWindowPos().x - ImGui::GetCursorPos().x, ImGui::GetWindowPos().y - ImGui::GetCursorPos().y};
    ImGui::PopStyleVar();

    static Vector2 lastViewportSize;
    viewportSize = {ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y};
    if(viewportSize != lastViewportSize)
    {
        onResize(viewportSize.x, viewportSize.y);
        lastViewportSize = viewportSize;
    }

    framebuffer->clearColorAttachment(2, -1);

    render(dt);
    ImGui::Image((ImTextureID)framebuffer->getColorAttachment()->getHandle(), {viewportSize.x, viewportSize.y}, {0, 1}, {1, 0}); // FIXME

    if(ImGui::IsWindowHovered())
    {
        hovered = true;

        // 选取实体
        if(ImGui::IsMouseClicked(ImGuiMouseButton_Left))
        {
            ImVec2 mouse = {ImGui::GetMousePos().x - viewportPos.x, ImGui::GetMousePos().y - viewportPos.y};

            int id;
            framebuffer->read(2, {0, 0}, id);
            Properties::entity = id == -1 ? Entity() : Entity(id, Main::registry);
        }

        // 自由视角
        locked = ImGui::IsMouseDown(ImGuiMouseButton_Right);
    }
    else
        hovered = false;

    ImGui::End();
}

void Viewport::attach()
{
    skyboxShader   = Shader::create("../assets/shaders/skybox_sphere.vert", "../assets/shaders/skybox_sphere.frag");
    standardShader = Shader::create("../assets/shaders/standard.vert", "../assets/shaders/standard.frag");

    auto win = Main::getWindow();

#if 1
    win->onScroll = [this](double xOfffset, double yOffset)
    {
        if(!hovered)
            return;

        static float fov = 60;
        if(1.f <= fov && fov <= 60.f)
            fov -= yOffset;
        fov = std::max(1.f, fov);
        fov = std::min(60.f, fov);
        camera.setPerspective(radians(fov), viewportSize.x / viewportSize.y, 0.1, 1000.f);
    };
#endif

    win->onMouseMove = [this](double x, double y)
    {
        static auto    speed = Vector2::unit * 0.09;
        static Vector2 last;

        if(!locked || !ImGui::IsMouseDown(ImGuiMouseButton_Right))
        {
            last   = Vector2(x, y);
            locked = false;
            return;
        }

        auto xOffset = x - last.x;
        auto yOffset = last.y - y;
        last         = Vector2(x, y);

        float sensitivity = 0.05;
        xOffset *= sensitivity;
        yOffset *= sensitivity;

        static float yaw = 90.0f, pitch = 0;
        yaw -= xOffset;
        pitch += yOffset;

        pitch = std::max(-89.f, pitch);
        pitch = std::min(89.f, pitch);

        Vector3 front;
        front.x = std::cos(radians(yaw)) * std::cos(radians(pitch));
        front.y = std::sin(radians(pitch));
        front.z = std::sin(radians(yaw)) * std::cos(radians(pitch));
        front.normalize();

        // camera.setDirection(camera.view.translate(), front);
        // camera.lookAt(camera.view.translate(), camera.view.translate() + front);

        // FIXME: 不是这样计算的
        // camera.view.rotateY(speed.x * radians(xOffset));
        // camera.view.rotateX(speed.y * radians(yOffset));
    };

    texture = Texture2D::create("../assets/textures/wall.jpg");

    camera.setDirection({0, 0, -30}, {0, 0, 1});
    camera.view.scale({2.1, 2.1, 2.1});
}

void Viewport::render(Time dt)
{
    updateLight(dt);
    updateCamera(dt);

    framebuffer->bind();
    glClearColor(.117f, .564f, 1.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT /* | GL_STENCIL_BUFFER_BIT*/);
    Main::registry.each<Mesh>([&](const Entity& e)
                              {
                                  if(e.get<Tag>().str == "skybox")
                                      e.get<Material>().shader = skyboxShader;
                                  else
                                      e.get<Material>().shader = standardShader;

                                  Renderer::get()->submit(e);
                              });
    framebuffer->unbind();

    ImGui::Text("%f, %f, %f", camera.view.translate().x, camera.view.translate().y, camera.view.translate().z);
}

void Viewport::onResize(float x, float y)
{
    // TODO: resize framebuffer
#if 1
    camera.setPerspective(radians(60), x / y, 0.1f, 1000.f);
#else
    camera.setOrthographic(size.x / 20, size.y / 20, -100.f, 100.f);
#endif
}

void Viewport::updateLight(Time dt)
{
    DirectionLight dirLights[1];
    dirLights[0].setDirection({1, -1, -1});
    for(int i = 0; i < 1; i++)
    {
        Vector3 ambient, diffuse, specular;
        dirLights[i].getColor(&ambient, &diffuse, &specular);
        standardShader->uploadUniform("u_direction_lights[" + std::to_string(i) + "].direction", dirLights[i].getDirection());
        standardShader->uploadUniform("u_direction_lights[" + std::to_string(i) + "].ambient", ambient);
        standardShader->uploadUniform("u_direction_lights[" + std::to_string(i) + "].diffuse", diffuse);
        standardShader->uploadUniform("u_direction_lights[" + std::to_string(i) + "].specular", specular);
    }

    /*
    PointLight pointLights[1];
    for(int i = 0; i < 1; i++)
    {
        Vector3 ambient, diffuse, specular;
        pointLights[i].getColor(&ambient, &diffuse, &specular);
        standardShader->uploadUniform("u_point_lights[" + std::to_string(i) + "].position", pointLights[i].getPosition());

        standardShader->uploadUniform("u_point_lights[" + std::to_string(i) + "].ambient", ambient);
        standardShader->uploadUniform("u_point_lights[" + std::to_string(i) + "].diffuse", diffuse);
        standardShader->uploadUniform("u_point_lights[" + std::to_string(i) + "].specular", specular);
    }
    */
}

void Viewport::updateCamera(Time dt)
{
    updateCameraControl(dt);

    skyboxShader->uploadUniform("u_view", camera.getViewMatrix());
    skyboxShader->uploadUniform("u_projection", camera.getProjectionMatrix());
    skyboxShader->uploadUniform("u_view_projection", camera.getViewProjectionMatrix());

    standardShader->uploadUniform("u_view", camera.getViewMatrix());
    standardShader->uploadUniform("u_projection", camera.getProjectionMatrix());
    standardShader->uploadUniform("u_view_projection", camera.getViewProjectionMatrix());

    standardShader->uploadUniform("u_cam_pos", camera.view.translate());
}

bool isKeyPressed(int key)
{
    auto win = Main::getWindow();
    return glfwGetKey((GLFWwindow*)win->nativeHandle(), key) == GLFW_PRESS;
}

void Viewport::updateCameraControl(Time dt)
{
    if(!ImGui::IsWindowHovered())
        return;

    float speed = 50 * dt.seconds();

    if(isKeyPressed(GLFW_KEY_LEFT_SHIFT))
        speed *= 3;

    if(isKeyPressed(GLFW_KEY_W))
        camera.view.translate(-Vector3::unit_z * speed);
    if(isKeyPressed(GLFW_KEY_S))
        camera.view.translate(Vector3::unit_z * speed);
    if(isKeyPressed(GLFW_KEY_A))
        camera.view.translate(Vector3::unit_x * speed);
    if(isKeyPressed(GLFW_KEY_D))
        camera.view.translate(-Vector3::unit_x * speed);
    if(isKeyPressed(GLFW_KEY_Q))
        camera.view.translate(Vector3::unit_y * speed);
    if(isKeyPressed(GLFW_KEY_E))
        camera.view.translate(-Vector3::unit_y * speed);

    if(isKeyPressed(GLFW_KEY_LEFT))
        camera.view.rotateY(radians(-0.5));
    else if(isKeyPressed(GLFW_KEY_RIGHT))
        camera.view.rotateY(radians(0.5));
    else if(isKeyPressed(GLFW_KEY_UP))
        camera.view.rotateX(radians(0.5));
    else if(isKeyPressed(GLFW_KEY_DOWN))
        camera.view.rotateX(radians(-0.5));
}

} // namespace clem::ui