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
    ImVec2 viewport = {ImGui::GetWindowPos().x - ImGui::GetCursorPos().x, ImGui::GetWindowPos().y - ImGui::GetCursorPos().y};
    ImGui::PopStyleVar();

    framebuffer->clearColorAttachment(2, -1);

    render(dt);
    ImGui::Image((ImTextureID)framebuffer->getColorAttachment()->getHandle(), ImGui::GetContentRegionAvail(), {0, 1}, {1, 0}); // FIXME

    if(ImGui::IsWindowHovered())
    {
        activated = true;

        // 选取实体
        if(ImGui::IsMouseClicked(ImGuiMouseButton_Left))
        {
            ImVec2 mouse = {ImGui::GetMousePos().x - viewport.x, ImGui::GetMousePos().y - viewport.y};

            int id;
            framebuffer->read(2, {0, 0}, id);
            Properties::entity = id == -1 ? Entity() : Entity(id, Main::registry);
        }

        // 自由视角
        locked = ImGui::IsMouseDown(ImGuiMouseButton_Right);
    }
    else
    {
        activated = false;
        move      = Vector3::zero;
    }

    ImGui::End();
}

void Viewport::attach()
{
    skyboxShader   = Shader::create("../assets/shaders/skybox.vert", "../assets/shaders/skybox.frag");
    standardShader = Shader::create("../assets/shaders/standard.vert", "../assets/shaders/standard.frag");

    auto win = Main::getWindow();

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

        camera.view.rotateY(speed.x * radians(x - last.x));
        camera.view.rotateX(speed.y * radians(last.y - y));
        last = Vector2(x, y);
    };

    win->onKey = [&](int action, int key)
    {
        if(!activated)
            return;

        const float speed = 0.1f;
        switch(action)
        {
        case GLFW_PRESS:
            switch(key)
            {
            case GLFW_KEY_ESCAPE:
                locked = false;
                break;

            case GLFW_KEY_W:
                move = -Vector3::unit_z * speed;
                // move = win->camera.view.forword().normalize() * 0.1;
                break;

            case GLFW_KEY_S:
                move = Vector3::unit_z * speed;
                // move = win->camera.view.back().normalize() * 0.1;
                break;

            case GLFW_KEY_A:
                move = Vector3::unit_x * speed;
                // move = win->camera.view.left().normalize() * 0.1;
                break;

            case GLFW_KEY_D:
                move = -Vector3::unit_x * speed;
                // move = win->camera.view.right().normalize() * 0.1;
                break;

            case GLFW_KEY_LEFT_SHIFT:
                move = Vector3::unit_y * speed;
                // move = -win->camera.view.up().normalize() * 0.1;
                break;

            case GLFW_KEY_SPACE:
                move = -Vector3::unit_y * speed;
                // move = -win->camera.view.down().normalize() * 0.1;
                break;
            }
            break;

        case GLFW_RELEASE:
            move = Vector3::zero;
            break;

        case GLFW_REPEAT:
            break;
        }
    };

    win->onScroll = [this](double xOfffset, double yOffset)
    {
        if(!activated)
            return;

        camera.view.scale(Vector3(1 + 0.1f * (float)yOffset, 1 + 0.1f * (float)yOffset, 1 + 0.1f * (float)yOffset));
    };

    win->onResize = [this](Size2 size)
    {
        onResize();
    };

    texture = Texture2D::create("../assets/textures/wall.jpg");

#if 1
    camera.setDirection({0, 0, 20}, {0, 0, -1}, -Vector3::unit_y);
#else
    camera.setDirection({0, 0, 20}, {0, 0, 1}, -Vector3::unit_y);
#endif

    light.translate({0, 1, 20});
}

void Viewport::render(Time dt)
{
    onResize();

    camera.view.translate(move);

    // 纹理
    // texture->bind();
    // standardShader->uploadUniform("u_texture", 0);

    // 光照
    light.rotateY(radians(60) * dt.seconds());
    standardShader->uploadUniform("u_light.position", light.translation());
    standardShader->uploadUniform("u_light.ambient", Vector3::unit * 1.0);
    standardShader->uploadUniform("u_light.diffuse", Vector3::unit * 1.0);
    standardShader->uploadUniform("u_light.specular", Vector3::unit * 1.0);

    skyboxShader->uploadUniform("u_view", camera.getViewMatrix());
    skyboxShader->uploadUniform("u_projection", camera.getProjectionMatrix());
    skyboxShader->uploadUniform("u_view_projection", camera.getViewProjectionMatrix());

    standardShader->uploadUniform("u_view", camera.getViewMatrix());
    standardShader->uploadUniform("u_projection", camera.getProjectionMatrix());
    standardShader->uploadUniform("u_view_projection", camera.getViewProjectionMatrix());

    framebuffer->bind();
    glClearColor(.117f, .564f, 1.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    Main::registry.each<Mesh>([&](const Entity& e)
                              {
                                  if(e.get<Tag>().str == "skybox")
                                      e.get<Material>().shader = skyboxShader;
                                  else
                                      e.get<Material>().shader = standardShader;

                                  Renderer::get()->submit(e);
                              });
    framebuffer->unbind();
}

void Viewport::onResize()
{
    Size2 size = {ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y};
#if 1
    camera.setPerspective(radians(60), size.x / size.y, 0.1f, 100.f);
#else
    camera.setOrthographic(size.x / 20, size.y / 20, -100.f, 100.f);
#endif
}

} // namespace clem::ui