// Copyright 2021 SMS
// License(Apache-2.0)

#include "Viewport.h"
#include "Browser.h"
#include "Profiler.h"
#include "Rendering/OpenGL/GLFrameBuffer.h"
#include "Window/GlfwWindow.h"
#include <ImGuizmo.h>
#include <glad/glad.h>
#include <imgui/imgui.h>

#include <glfw/glfw3.h>

namespace clem::ui
{

void Viewport::attach()
{
    geometryShader = Shader::load("geometry");
    lightingShader = Shader::load("lighting");

    forwardShader = Shader::load("forward");
    shadowShader  = Shader::load("shadow");
    skyboxShader  = Shader::load("skybox_sphere");

    auto win = Main::getWindow();

    win->setSync(Configuration::Display::vsync);

    win->onScroll = [this](double xOffset, double yOffset)
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
        static auto    speed       = Vector2::unit * 1;
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

        xOffset *= Configuration::Controls::mouseSensitivity.x;
        yOffset *= Configuration::Controls::mouseSensitivity.y;

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

        camera.view.rotation = {-pitch, -yaw, 0.f};

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
    dirLights[0].setIntesity(1.f);
    dirLights[0].setDirection({-0.5, -1, -0.5});

    Random random;
    pointLights.resize(16);
    for(size_t i = 0; i < 16; i++)
    {
        pointLights[i].setColor(random.getVector3({0.5, 0.5, 0.5}, {1, 1, 1}));
        pointLights[i].setIntesity(2.f);
        pointLights[i].setPosition(random.getVector3({-30, 0, -100}, {30, 80, 100}));
    }

    // dirLights.clear();
    pointLights.clear();
}

void Viewport::update(Time dt)
{
    PROFILE_FUNC();

    toolbar();

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{0, 0});
    ImGui::Begin("Viewport", &visible);
    viewportPos = {ImGui::GetWindowPos().x - ImGui::GetCursorPos().x, ImGui::GetWindowPos().y - ImGui::GetCursorPos().y};
    ImGui::PopStyleVar();

    // 窗口大小发生变化时, 调用 onResize()
    static Vector2 lastViewportSize;
    viewportSize = {ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y};
    if(viewportSize != lastViewportSize)
    {
        onResize(viewportSize);
        lastViewportSize = viewportSize;
    }

    framebuffer->clearColorAttachment(1, -1);

#if 1
    deferredRender(dt);
#else
    forwardRender(dt);
#endif

    // ImGui::Image((ImTextureID)framebuffer->getColorAttachment()->getHandle(), {viewportSize.x, viewportSize.y}, {1, 1}, {0, 0});
    ImGui::Image((ImTextureID)gbuffer.getTexture(GBuffer::TextureType::Normals)->getHandle(), {viewportSize.x, viewportSize.y}, {1, 1}, {0, 0});

    if(status == Status::Playing)
    {
        ImGui::End();
        return;
    }

    updateCameraControl(dt);
    gizmos();
    mousePicking();

    // TODO: 临时场景相机信息, 移动到 toolbar
    ImGui::Text("CAM: POS(%.3f,%.3f,%.3f) DIR(%.3f,%.3f,%.3f)", camera.view.translation.x, camera.view.translation.y, camera.view.translation.z,
                Matrix4(camera.view).forword().normalize().x, Matrix4(camera.view).forword().normalize().y, Matrix4(camera.view).forword().normalize().z);
    // ImGui::Text("POS(%.3f,%.3f,%.3f)", camera.view.translation.x, camera.view.translation.y, camera.view.translation.z);
    // ImGui::Text("DIR(%.3f,%.3f,%.3f)", Matrix4(camera.view).forword().normalize().x, Matrix4(camera.view).forword().normalize().y, Matrix4(camera.view).forword().normalize().z);

    ImGui::End();
}

void Viewport::deferredRender(Time dt)
{
    {
        const auto  writeTime     = fs::last_write_time("../assets/shaders/geometry.frag");
        static auto lastWriteTime = writeTime;
        if(writeTime != lastWriteTime)
        {
            forwardShader = Shader::reload("forward");
            lastWriteTime = writeTime;
        }
    }
    {
        const auto  writeTime     = fs::last_write_time("../assets/shaders/lighting.frag");
        static auto lastWriteTime = writeTime;
        if(writeTime != lastWriteTime)
        {
            forwardShader = Shader::reload("forward");
            lastWriteTime = writeTime;
        }
    }

    geometryPass();
    lightingPass();
}

void Viewport::forwardRender(Time dt)
{
    PROFILE_FUNC();

    const auto  writeTime     = fs::last_write_time("../assets/shaders/forward.frag");
    static auto lastWriteTime = writeTime;
    if(writeTime != lastWriteTime)
    {
        forwardShader = Shader::reload("forward");
        lastWriteTime = writeTime;
    }

    uploadLights(forwardShader);
    updateShadow(dt);
    uploadCamera(forwardShader);

    const auto size = framebuffer->getSize();
    Renderer::get()->setViewport(0, 0, size.x, size.y);
    framebuffer->bind();
    glClearColor(.117f, .564f, 1.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT /* | GL_STENCIL_BUFFER_BIT*/);
    Main::registry.each<Model>([&](const Entity& e)
                               { Renderer::get()->submit(e); });
    framebuffer->unbind();
}

void Viewport::geometryPass()
{
    glDepthMask(GL_TRUE);
    glEnable(GL_DEPTH_TEST);

    uploadCamera(geometryShader);
    gbuffer.bind();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    geometryShader->bind();
    geometryShader->uploadUniform("u_view", camera.getViewMatrix());
    geometryShader->uploadUniform("u_projection", camera.getProjectionMatrix());
    geometryShader->uploadUniform("u_view_projection", camera.getViewProjectionMatrix());
    Main::registry.each<Model>([&](const Entity& e)
                               { Renderer::get()->submit(e, geometryShader); });
    gbuffer.unbind();

    glDepthMask(GL_FALSE);
    glDisable(GL_DEPTH_TEST);
}

void Viewport::lightingPass()
{
    // glEnable(GL_BLEND);
    // glBlendEquation(GL_FUNC_ADD);
    // glBlendFunc(GL_ONE, GL_ONE);

    glClear(GL_COLOR_BUFFER_BIT);
    lightingShader->bind();
    gbuffer.getTexture(GBuffer::TextureType::Position)->bind(0);
    lightingShader->uploadUniform("position", 0);
    gbuffer.getTexture(GBuffer::TextureType::Normals)->bind(1);
    lightingShader->uploadUniform("normal", 1);
    gbuffer.getTexture(GBuffer::TextureType::AlbedoSpec)->bind(2);
    lightingShader->uploadUniform("albedo_spec", 2);
    uploadCamera(lightingShader);
    uploadLights(lightingShader);
    Main::registry.each<Model>([&](const Entity& e)
                               { ; });
}

void Viewport::toolbar()
{
    static auto playIcon = Texture2D::create("../assets/textures/icons/play_button.png");
    static auto stopIcon = Texture2D::create("../assets/textures/icons/stop_button.png");

    ImGui::Begin("##toolbar", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

    // 开始/结束 按钮
    float                      size = ImGui::GetWindowHeight() - 4.0f;
    std::shared_ptr<Texture2D> icon = status == Status::Stopping ? playIcon : stopIcon;
    ImGui::SetCursorPosX((ImGui::GetWindowContentRegionMax().x * 0.5f) - (size * 0.5f));

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 2));
    ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(0, 0));
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
    auto&       colors        = ImGui::GetStyle().Colors;
    const auto& buttonHovered = colors[ImGuiCol_ButtonHovered];
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(buttonHovered.x, buttonHovered.y, buttonHovered.z, 0.5f));
    const auto& buttonActive = colors[ImGuiCol_ButtonActive];
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(buttonActive.x, buttonActive.y, buttonActive.z, 0.5f));

    if(ImGui::ImageButton((ImTextureID)icon->getHandle(), ImVec2(size, size), ImVec2(0, 0), ImVec2(1, 1), 0))
    {
        if(status == Status::Playing)
            stopScene();
        else
            playScene();
    }

    ImGui::PopStyleVar(2);
    ImGui::PopStyleColor(3);

    ImGui::End();
}

void Viewport::gizmos()
{
    // 辅助线框
    auto& entity = Properties::entity;
    if(entity.valid() && entity.anyOf<Transform>())
    {
        ImGuizmo::SetOrthographic(camera.getType() == Camera::Type::Orthographic);
        ImGuizmo::SetDrawlist();

        const auto pos  = ImGui::GetWindowPos();
        const auto size = ImGui::GetWindowSize();
        // ImGuizmo::SetRect(pos.x, pos.y, size.x, size.y);
        ImGuizmo::SetRect(pos.x, pos.y, size.x, size.y);

        auto& transform = entity.get<Transform>();

        const auto& view  = camera.getViewMatrix();
        const auto& proj  = camera.getProjectionMatrix();
        Matrix4     model = transform.getModelMatrix();

        ImGuizmo::Manipulate(view.data(), proj.data(), ImGuizmo::OPERATION::TRANSLATE, ImGuizmo::LOCAL, model.data());

        if(ImGuizmo::IsUsing())
        {
            // FIXME: 完善旋转
            Vector3 a;
            ImGuizmo::DecomposeMatrixToComponents(model.data(), transform.translation.data(), a.data(), transform.scale.data());
        }
    }
}

void Viewport::mousePicking()
{
    // 鼠标选取
    if(ImGui::IsWindowHovered())
    {
        hovered = true;

        if(!ImGuizmo::IsOver() && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
        {
            Vector2 mouse = {ImGui::GetMousePos().x - viewportPos.x, ImGui::GetMousePos().y - viewportPos.y};

            int id;
            framebuffer->readColorAttachment(1, mouse, id);
            Properties::entity = id == -1 ? Entity() : Entity(id, Main::registry);
        }

        // 鼠标右键是否按下
        locked = ImGui::IsMouseDown(ImGuiMouseButton_Right);
    }
    else
        hovered = false;
}

void Viewport::playScene()
{
    status = Status::Playing;
}

void Viewport::stopScene()
{
    status = Status::Stopping;
}

void Viewport::onResize(Size2 size)
{
    // 重新生成相机投影矩阵
    if(camera.getType() == Camera::Type::Perspective)
        camera.setPerspective(radians(60), size.x / size.y, 0.03f, 10000.f);
    else
        camera.setOrthographic(size.x / 20, size.y / 20, -100.f, 100.f);
}

void Viewport::uploadCamera(std::shared_ptr<Shader> shader)
{
    PROFILE_FUNC();

    skyboxShader->uploadUniform("u_view", camera.getViewMatrix());
    skyboxShader->uploadUniform("u_projection", camera.getProjectionMatrix());
    skyboxShader->uploadUniform("u_view_projection", camera.getViewProjectionMatrix());

    shader->uploadUniform("u_view", camera.getViewMatrix());
    shader->uploadUniform("u_projection", camera.getProjectionMatrix());
    shader->uploadUniform("u_view_projection", camera.getViewProjectionMatrix());
}

void Viewport::uploadLights(std::shared_ptr<Shader> shader)
{
    PROFILE_FUNC();

    shader->uploadUniform("u_direction_lights_size", (int)dirLights.size());
    for(int i = 0; i < dirLights.size(); i++)
    {
        const auto name = "u_direction_lights[" + std::to_string(i) + "].";
        shader->uploadUniform(name + "color", dirLights[i].getColor());
        shader->uploadUniform(name + "intesity", dirLights[i].getIntesity());

        shader->uploadUniform(name + "direction", dirLights[i].getDirection());
    }

    shader->uploadUniform("u_point_lights_size", (int)pointLights.size());
    for(int i = 0; i < pointLights.size(); i++)
    {
        const auto name = "u_point_lights[" + std::to_string(i) + "].";
        shader->uploadUniform(name + "color", pointLights[i].getColor());
        shader->uploadUniform(name + "intesity", pointLights[i].getIntesity());

        shader->uploadUniform(name + "position", pointLights[i].getPosition());

        shader->uploadUniform(name + "constant", 1.0f);
        shader->uploadUniform(name + "linear", 0.09f);
        shader->uploadUniform(name + "quadratic", 0.032f);
    }

    shader->uploadUniform("u_spot_lights_size", (int)spotLights.size());
    for(int i = 0; i < spotLights.size(); i++)
    {
        const auto name = "u_spot_lights[" + std::to_string(i) + "].";
        shader->uploadUniform(name + "color", spotLights[i].getColor());
        shader->uploadUniform(name + "intesity", spotLights[i].getIntesity());

        shader->uploadUniform(name + "direction", spotLights[i].getDirection());
        shader->uploadUniform(name + "position", spotLights[i].getPosition());

        shader->uploadUniform(name + "constant", 1.0f);
        shader->uploadUniform(name + "linear", 0.09f);
        shader->uploadUniform(name + "quadratic", 0.032f);
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

void Viewport::updateCameraControl(Time dt)
{
    if(!ImGui::IsWindowHovered())
        return;

    float speed = 40 * dt.seconds();

    if(Input::isPressed(KeyCode::LShift))
        speed *= 3;

#if 0
    if(Input::isKeyPressed(KeyCode::W))
        camera.view.translation += Matrix4(camera.view).forword().normalize() * speed;
    if(Input::isKeyPressed(KeyCode::S))
        camera.view.translation += Matrix4(camera.view).back().normalize() * speed;
    if(Input::isKeyPressed(KeyCode::A))
        camera.view.translation += Matrix4(camera.view).left().normalize() * speed;
    if(Input::isKeyPressed(KeyCode::D))
        camera.view.translation += Matrix4(camera.view).right().normalize() * speed;
    if(Input::isKeyPressed(KeyCode::E))
        camera.view.translation += Matrix4(camera.view).up().normalize() * speed;
    if(Input::isKeyPressed(KeyCode::Q))
        camera.view.translation += Matrix4(camera.view).down().normalize() * speed;
#else
    if(Input::isPressed(KeyCode::W))
        camera.view.translation += -Vector3::unit_z * speed;
    if(Input::isPressed(KeyCode::S))
        camera.view.translation += Vector3::unit_z * speed;
    if(Input::isPressed(KeyCode::A))
        camera.view.translation += -Vector3::unit_x * speed;
    if(Input::isPressed(KeyCode::D))
        camera.view.translation += Vector3::unit_x * speed;
    if(Input::isPressed(KeyCode::E))
        camera.view.translation += -Vector3::unit_y * speed;
    if(Input::isPressed(KeyCode::Q))
        camera.view.translation += Vector3::unit_y * speed;
#endif

    if(Input::isPressed(KeyCode::Left))
        camera.view.rotation.y += -0.5;
    else if(Input::isPressed(KeyCode::Right))
        camera.view.rotation.y += 0.5;
    else if(Input::isPressed(KeyCode::Up))
        camera.view.rotation.x += -0.5;
    else if(Input::isPressed(KeyCode::Down))
        camera.view.rotation.x += 0.5;

    if(Input::isPressed(KeyCode::W))
        camera.view_.translate(Vector3::unit_z * speed);

    Vector3 pos = camera.view_.translate();

    camera.view_.translate(camera.view_.translate() - pos);

    if(Input::isPressed(KeyCode::Left))
        camera.view_.rotateY(radians(0.5));
    if(Input::isPressed(KeyCode::Right))
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