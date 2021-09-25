// Copyright 2021 SMS
// License(Apache-2.0)

#include "Viewport.h"
#include "Browser.h"
#include "Profiler.h"
#include "Rendering/OpenGL/GLFrameBuffer.h"
#include "Window/GlfwWindow.h"
#include <glad/glad.h>
#include <imgui/imgui.h>

#include <glfw/glfw3.h>

namespace clem::ui
{

void Viewport::attach()
{
    standardShader = Shader::create("standard");
    shadowShader   = Shader::create("shadow");
    skyboxShader   = Shader::create("skybox_sphere");

    auto win = Main::getWindow();

    win->setSync(false);

    win->onScroll = [this](double xOfffset, double yOffset)
    {
        if(!hovered)
            return;

        static float fov = 60;
        if(1.f <= fov && fov <= 60.f)
            fov -= (float)yOffset;
        fov = std::max(1.f, fov);
        fov = std::min(60.f, fov);
        camera.setPerspective(radians(fov), viewportSize.x / viewportSize.y, 0.03f, 10000.f);
    };

    win->onMouseMove = [this](double x, double y)
    {
        static auto    speed = Vector2::unit * 1;
        static Vector2 last;

        if(!locked || !ImGui::IsMouseDown(ImGuiMouseButton_Right))
        {
            last   = {(float)x, (float)y};
            locked = false;
            return;
        }

        auto xOffset = (float)x - last.x;
        auto yOffset = last.y - (float)y;
        last         = {(float)x, (float)y};

        float sensitivity = 0.05;
        xOffset *= sensitivity;
        yOffset *= sensitivity;

        static float yaw = 180.f, pitch = 0.f;
        yaw -= xOffset;
        pitch += yOffset;

        pitch = std::max(-89.f, pitch);
        pitch = std::min(89.f, pitch);

        Vector3 front;
        front.x = std::cos(radians(yaw)) * std::cos(radians(pitch));
        front.y = std::sin(radians(pitch));
        front.z = std::sin(radians(yaw)) * std::cos(radians(pitch));
        front.normalize();

        camera.view.rotation = {-pitch, yaw, 0.f};

        // camera.setDirection(camera.view.translate(), front);
        // camera.lookAt(camera.view.translate(), camera.view.translate() + front);

        // camera.view.rotateY(speed.x * radians(xOffset));
        // camera.view.rotateX(speed.y * radians(yOffset));
    };

    // camera.setDirection({0, 0, -30}, {0, 0, 1});
    camera.view.translation = {0.f, 0.f, -30.f};
    camera.view.rotation    = {0.f, 180.f, 0.f};
    camera.view.scale       = {2.1f, 2.1f, 2.1f};

    dirLights.resize(1);
    dirLights[0].setColor({255.f / 255.f, 244.f / 255.f, 214.f / 255.f});
    dirLights[0].setIntesity(2.f);
    dirLights[0].setDirection({-0.5, -1, -0.5});

    pointLights.resize(2);
    pointLights[0].setColor({1, 0, 0});
    pointLights[0].setIntesity(1.f);
    pointLights[0].setPosition({5, 5, 0});
    pointLights[1].setColor({0, 1, 0});
    pointLights[1].setIntesity(1.f);
    pointLights[1].setPosition({-5, 5, 0});

    pointLights.clear();
}

void Viewport::update(Time dt)
{
    PROFILE_FUNC();

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

    framebuffer->clearColorAttachment(1, -1);

    render(dt);
    ImGui::Image((ImTextureID)framebuffer->getColorAttachment()->getHandle(), {viewportSize.x, viewportSize.y}, {1, 1}, {0, 0});

    ImGui::Text("CAM: POS(%.3f,%.3f,%.3f) DIR(%.3f,%.3f,%.3f)", camera.view.translation.x, camera.view.translation.y, camera.view.translation.z,
                Matrix4(camera.view).forword().normalize().x, Matrix4(camera.view).forword().normalize().y, Matrix4(camera.view).forword().normalize().z);

    if(ImGui::IsWindowHovered())
    {
        hovered = true;

        // 鼠标选取
        if(ImGui::IsMouseClicked(ImGuiMouseButton_Left))
        {
            Vector2 mouse = {ImGui::GetMousePos().x - viewportPos.x, ImGui::GetMousePos().y - viewportPos.y};

            int id;
            framebuffer->readColorAttachment(1, mouse, id); // FIXME
            Properties::entity = id == -1 ? Entity() : Entity(id, Main::registry);
        }

        // 鼠标右键是否按下
        locked = ImGui::IsMouseDown(ImGuiMouseButton_Right);
    }
    else
        hovered = false;

    ImGui::End();
}

void Viewport::render(Time dt)
{
    PROFILE_FUNC();

    updateLight(dt);
    updateShadow(dt);
    updateCamera(dt);

    const auto size = framebuffer->getSize();
    Renderer::get()->setViewport(0, 0, size.x, size.y);
    framebuffer->bind();
    glClearColor(.117f, .564f, 1.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT /* | GL_STENCIL_BUFFER_BIT*/);
    Main::registry.each<Model>([&](const Entity& e)
                               { Renderer::get()->submit(e); });
    framebuffer->unbind();
}

void Viewport::onResize(float x, float y)
{
    // TODO: resize framebuffer
#if 1
    camera.setPerspective(radians(60), x / y, 0.03f, 10000.f);
#else
    camera.setOrthographic(size.x / 20, size.y / 20, -100.f, 100.f);
#endif
}

void Viewport::updateLight(Time dt)
{
    PROFILE_FUNC();

    standardShader->uploadUniform("u_direction_lights_size", (int)dirLights.size());
    for(int i = 0; i < dirLights.size(); i++)
    {
        const auto name = "u_direction_lights[" + std::to_string(i) + "].";
        standardShader->uploadUniform(name + "color", dirLights[i].getColor());
        standardShader->uploadUniform(name + "intesity", dirLights[i].getIntesity());
        standardShader->uploadUniform(name + "direction", dirLights[i].getDirection());
    }

    standardShader->uploadUniform("u_point_lights_size", (int)pointLights.size());
    for(int i = 0; i < pointLights.size(); i++)
    {
        const auto name = "u_point_lights[" + std::to_string(i) + "].";
        standardShader->uploadUniform(name + "color", pointLights[i].getColor());
        standardShader->uploadUniform(name + "intesity", pointLights[i].getIntesity());
        standardShader->uploadUniform(name + "position", pointLights[i].getPosition());
    }

    standardShader->uploadUniform("u_spot_lights_size", (int)spotLights.size());
    for(int i = 0; i < spotLights.size(); i++)
    {
        const auto name = "u_spot_lights[" + std::to_string(i) + "].";
        standardShader->uploadUniform(name + "color", spotLights[i].getColor());
        standardShader->uploadUniform(name + "intesity", spotLights[i].getIntesity());
        standardShader->uploadUniform(name + "direction", spotLights[i].getDirection());
        standardShader->uploadUniform(name + "position", spotLights[i].getPosition());
    }
}

void Viewport::updateShadow(Time dt)
{
    PROFILE_FUNC();

    const auto size = shadowMap->getSize();
    Renderer::get()->setViewport(0, 0, size.x, size.y);

    static Camera shadowCam;

    for(const auto& light : dirLights)
    {
        shadowCam.setOrthographic(10, 10, 0.1f, 10.f);

        shadowShader->uploadUniform("u_view", camera.getViewMatrix());
        shadowShader->uploadUniform("u_projection", camera.getProjectionMatrix());
        // shadowShader->uploadUniform("u_view_projection", camera.getViewProjectionMatrix());

        shadowMap->bind();
        glClear(GL_DEPTH_BUFFER_BIT);
        /*
        Main::registry.each<Model>([&](const Entity& e)
                                   { Renderer::get()->submit(e, shadowShader); });
        */
        shadowMap->unbind();
    }
}

void Viewport::updateCamera(Time dt)
{
    PROFILE_FUNC();

    updateCameraControl(dt);

    skyboxShader->uploadUniform("u_view", camera.getViewMatrix());
    skyboxShader->uploadUniform("u_projection", camera.getProjectionMatrix());
    skyboxShader->uploadUniform("u_view_projection", camera.getViewProjectionMatrix());

    standardShader->uploadUniform("u_view", camera.getViewMatrix());
    standardShader->uploadUniform("u_projection", camera.getProjectionMatrix());
    standardShader->uploadUniform("u_view_projection", camera.getViewProjectionMatrix());
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

    float speed = 40 * dt.seconds();

    if(isKeyPressed(GLFW_KEY_LEFT_SHIFT))
        speed *= 3;

#if 0
    if(isKeyPressed(GLFW_KEY_W))
        camera.view.translation += Matrix4(camera.view).forword().normalize() * speed;
    if(isKeyPressed(GLFW_KEY_S))
        camera.view.translation += Matrix4(camera.view).back().normalize() * speed;
    if(isKeyPressed(GLFW_KEY_A))
        camera.view.translation += Matrix4(camera.view).left().normalize() * speed;
    if(isKeyPressed(GLFW_KEY_D))
        camera.view.translation += Matrix4(camera.view).right().normalize() * speed;
    if(isKeyPressed(GLFW_KEY_E))
        camera.view.translation += Matrix4(camera.view).up().normalize() * speed;
    if(isKeyPressed(GLFW_KEY_Q))
        camera.view.translation += Matrix4(camera.view).down().normalize() * speed;
#else
    if(isKeyPressed(GLFW_KEY_W))
        camera.view.translation += -Vector3::unit_z * speed;
    if(isKeyPressed(GLFW_KEY_S))
        camera.view.translation += Vector3::unit_z * speed;
    if(isKeyPressed(GLFW_KEY_A))
        camera.view.translation += -Vector3::unit_x * speed;
    if(isKeyPressed(GLFW_KEY_D))
        camera.view.translation += Vector3::unit_x * speed;
    if(isKeyPressed(GLFW_KEY_E))
        camera.view.translation += -Vector3::unit_y * speed;
    if(isKeyPressed(GLFW_KEY_Q))
        camera.view.translation += Vector3::unit_y * speed;
#endif

    if(isKeyPressed(GLFW_KEY_LEFT))
        camera.view.rotation.y += -0.5;
    else if(isKeyPressed(GLFW_KEY_RIGHT))
        camera.view.rotation.y += 0.5;
    else if(isKeyPressed(GLFW_KEY_UP))
        camera.view.rotation.x += -0.5;
    else if(isKeyPressed(GLFW_KEY_DOWN))
        camera.view.rotation.x += 0.5;

    if(isKeyPressed(GLFW_KEY_W))
        camera.view_.translate(Vector3::unit_z * speed);

    Vector3 pos = camera.view_.translate();

    camera.view_.translate(camera.view_.translate() - pos);

    if(isKeyPressed(GLFW_KEY_LEFT))
        camera.view_.rotateY(radians(0.5));
    if(isKeyPressed(GLFW_KEY_RIGHT))
        camera.view_.rotateY(radians(-0.5));

    camera.view_.translate(pos);

    /*
    static Transform transform;

    Vector3 rotate;
    if(isKeyPressed(GLFW_KEY_RIGHT))
        rotate.y += 1.f;
    if(isKeyPressed(GLFW_KEY_LEFT))
        rotate.y -= 1.f;
    if(isKeyPressed(GLFW_KEY_UP))
        rotate.x += 1.f;
    if(isKeyPressed(GLFW_KEY_DOWN))
        rotate.x -= 1.f;

    if(rotate.dot(rotate) > std::numeric_limits<float>::epsilon())
        transform.rotation += rotate.getNormalized() * speed * dt.seconds();

    // limit pitch values between about +/- 85ish degrees
    transform.rotation.x = std::clamp(transform.rotation.x, -89.f, 89.f);
    // transform.rotation.y = transform.rotation.y % 360.f;

    float         yaw = transform.rotation.y;
    const Vector3 forward(std::sin(yaw), 0.f, std::cos(yaw));
    const Vector3 right(forward.z, 0.f, -forward.x);
    const Vector3 up(0.f, -1.f, 0.f);

    Vector3 move;
    if(isKeyPressed(GLFW_KEY_W))
        move += forward;
    if(isKeyPressed(GLFW_KEY_S))
        move -= forward;
    if(isKeyPressed(GLFW_KEY_D))
        move += right;
    if(isKeyPressed(GLFW_KEY_A))
        move -= right;
    if(isKeyPressed(GLFW_KEY_E))
        move += up;
    if(isKeyPressed(GLFW_KEY_Q))
        move -= up;

    if(move.dot(move) > std::numeric_limits<float>::epsilon())
        transform.translation += move.getNormalized() * speed * dt.seconds();

    camera.view = transform;
    */
}

} // namespace clem::ui