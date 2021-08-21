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

    // ImGui::IsWindowFocused()
    if(ImGui::IsWindowHovered())
    {
        active = true;

        // 选取实体
        if(ImGui::IsMouseClicked(ImGuiMouseButton_Left))
        {
            ImVec2 mouse = {ImGui::GetMousePos().x - viewport.x, ImGui::GetMousePos().y - viewport.y};

            int id;
            framebuffer->read(2, {0, 0}, id);
            Properties::entity = id == -1 ? Entity() : Entity(id, Main::registry);
        }
    }
    else
    {
        active = false;
        move   = Vector3::zero;
    }

    ImGui::End();
}

void Viewport::attach()
{
    skyboxShader = Shader::create(R"(
		#version 450

		layout(location = 0) in vec3 a_position;

        uniform mat4 u_view;
        uniform mat4 u_projection;

        out vec3 v_uvw;

		void main()
		{
            v_uvw = a_position;
			gl_Position = u_projection * u_view * vec4(a_position, 1.0);
		}
	)",
                                  R"(
		#version 450

        in vec3 v_uvw;

        uniform samplerCube u_skybox;

		void main()
		{
            gl_FragColor = texture(u_skybox, v_uvw);
		}
	)");

    standardShader = Shader::create(R"(
		#version 450

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
            v_normal    = normalize(mat3(transpose(inverse(u_model))) * a_normal);
            v_uv        = a_uv;

            v_cam_position = vec3(u_view[3][0], u_view[3][1], u_view[3][2]);

			gl_Position = u_projection * u_view * u_model * vec4(a_position, 1.0);
		}
	)",
                                    R"(
		#version 450

        struct Light
        {
            vec3 position;

            vec3 ambient;
            vec3 diffuse;
            vec3 specular;
        };

        struct DirectionLight
        {
            vec3 direction;

            vec3 ambient;
            vec3 diffuse;
            vec3 specular;
        };

        struct PointLight
        {
            vec3 position;

            float constant;
            float linear;
            float quadratic;

            vec3 ambient;
            vec3 diffuse;
            vec3 specular;
        };

        struct SpotLight
        {
            vec3 direction;

            vec3 ambient;
            vec3 diffuse;
            vec3 specular;
        };

        struct Material
        {
            vec3  ambient;
            vec3  diffuse;
            vec3  specular;
            float shininess;
        };

        layout (location = 0) out vec4 frag_color;
        layout (location = 1) out vec4 bright_color;
        layout (location = 2) out int  entity_id;

        in vec3 v_position;
        in vec3 v_color;
        in vec3 v_normal;
        in vec2 v_uv;

        in vec3 v_cam_position;

        uniform Light     u_light;
        uniform Material  u_material;
        uniform sampler2D u_texture;
        uniform int       u_entity_id;

        vec4 lighting();

		void main()
		{
            frag_color = vec4(1.0, 1.0, 1.0, 1.0) * lighting();
            // frag_color = texture(u_texture, vec2(1.0 - v_uv.x, v_uv.y)) * lighting();

            // 提取亮色
            float brightness = dot(frag_color.rgb, vec3(0.2126, 0.7152, 0.0722));
            if(brightness > 1.0)
                bright_color = vec4(frag_color.rgb, 1.0);

            entity_id = u_entity_id;
		}

        // 计算平行光照
        vec3 CalcDirLight(DirectionLight light, vec3 normal, vec3 dir_to_cam)
        {
            vec3 dir_to_light = normalize(-light.direction);

            // 环境光照
            vec3 ambient = light.ambient * u_material.ambient;

            // 漫反射光照
            float diffuse_amount = max(0.0, dot(dir_to_light, v_normal));
            vec3  diffuse        = light.diffuse * (diffuse_amount * u_material.diffuse);

            // 镜面反射光照
            vec3  reflected_direction = reflect(dir_to_light, v_normal);
            float specular_amount     = pow(max(0.0, dot(reflected_direction, dir_to_cam)), u_material.shininess);
            vec3  specular            = light.specular * (specular_amount * u_material.specular);

            return ambient + diffuse + specular;
        }

        // 计算点光源光照
        vec3 CalcPointLight(PointLight light, vec3 normal, vec3 dir_to_cam)
        {
            vec3 dir_to_light = normalize(light.position - v_position);

            // 衰减率
            float distance    = length(light.position - v_position);
            float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

            return CalcDirLight(DirectionLight(-dir_to_light, light.ambient, light.diffuse, light.specular), normal, dir_to_cam) * attenuation;
        }

        // 计算总光照
        vec4 CalcLighting()
        {
            vec3 light;
            return vec4(light, 1.0);
        }

        vec4 lighting()
        {
            vec3 direction_to_light = normalize(u_light.position - v_position);
            vec3 direction_to_cam   = normalize(v_position - v_cam_position);

            // 环境光照
            const vec3 ka            = u_material.ambient;
            const vec3 ia            = u_light.ambient;
            vec3       ambient_light = ka * ia;

            // 漫反射光照
            const vec3 kd                  = u_material.diffuse;
            const vec3 id                  = u_light.diffuse;
            float      amont_diffuse_light = max(0.0, dot(direction_to_light, v_normal));
            vec3       diffuse_light       = kd * amont_diffuse_light * id;

            // 镜面反射光照
            const vec3 ks                    = u_material.specular;
            const vec3 is                    = u_light.specular;
            vec3       reflected_light       = reflect(direction_to_light, v_normal);
            float      shininess             = u_material.shininess;
            float      amount_specular_light = pow(max(0.0, dot(reflected_light, direction_to_cam)), shininess);
            vec3       specular_light        = ks * amount_specular_light * is;

            return vec4(ambient_light + diffuse_light + specular_light, 1.0);
        }

        /*
        struct Material
        {
            sampler2D diffuse;
            sampler2D specular;
            float     shininess;
        };

        vec4 CalcDirLight(DirectionLight light, vec3 normal, vec3 direction_to_cam)
        {
            vec3 direction_to_light = normalize(-light.direction);

            // 环境光照
            vec3 ambient = light.ambient * vec3(texture(u_material.diffuse, v_uv));

            // 漫反射光照
            float diffuse_amount = max(0.0, dot(direction_to_light, v_normal));
            vec3  diffuse        = light.diffuse * diffuse_amount * vec3(texture(u_material.diffuse, v_uv));

            // 镜面反射光照
            vec3  reflected_direction = reflect(direction_to_light, v_normal);
            float specular_amount     = pow(max(0.0, dot(reflected_light, direction_to_cam)), u_material.shininess);
            vec3  specular            = light.specular * specular_amount * vec3(texture(u_material.specular, v_uv));
        }
        */
	)");

    auto win = Main::getWindow();

#if 0
    win->onMouseMove = [this](double x, double y)
    {
        if(!active)
            return;

        static Vector2 last;
        static auto    speed = Vector2::unit * 0.09;

        camera.view.rotateY(speed.x * radians(x - last.x));
        camera.view.rotateX(speed.y * radians(last.y - y));
        last = Vector2(x, y);
    };
#endif

    win->onKey = [&](int action, int key)
    {
        if(!active)
            return;

        const float speed = 0.1f;
        switch(action)
        {
        case GLFW_PRESS:
            switch(key)
            {
            case GLFW_KEY_ESCAPE:
                win->onClose();
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
        if(!active)
            return;

        camera.view.scale(Vector3(1 + 0.1f * (float)yOffset, 1 + 0.1f * (float)yOffset, 1 + 0.1f * (float)yOffset));
    };

    win->onResize = [this](Size2 size)
    {
        onResize();
    };

    skybox = Texture2D::create();
    skybox->loadCubemap(
        {
            "../assets/textures/skybox/right.jpg",
            "../assets/textures/skybox/left.jpg",
            "../assets/textures/skybox/top.jpg",
            "../assets/textures/skybox/bottom.jpg",
            "../assets/textures/skybox/back.jpg",
            "../assets/textures/skybox/front.jpg",
        });

    texture = Texture2D::create("../assets/textures/wall.jpg");

#if 1
    camera.setDirection({0, 0, 20}, {0, 0, -1}, -Vector3::unit_y);
#else
    camera.setDirection({0, 0, 20}, {0, 0, 1}, -Vector3::unit_y);
#endif

    light.translate({0, 1, 0});
}

void Viewport::render(Time dt)
{
    onResize();

    camera.view.translate(move);

    // 天空盒
    skybox->bind();
    skyboxShader->uploadUniform("u_skybox", 0);

    // 纹理
    // texture->bind();
    // standardShader->uploadUniform("u_texture", 0);

    // 光照
    // light.rotateY(radians(60) * dt.seconds());
    standardShader->uploadUniform("u_light.position", light.translation());
    standardShader->uploadUniform("u_light.ambient", Vector3::unit * 1.0);
    standardShader->uploadUniform("u_light.diffuse", Vector3::unit * 1.0);
    standardShader->uploadUniform("u_light.specular", Vector3::unit * 1.0);

    standardShader->uploadUniform("u_view", camera.getViewMatrix());
    standardShader->uploadUniform("u_projection", camera.getProjectionMatrix());
    standardShader->uploadUniform("u_view_projection", camera.getViewProjectionMatrix());

    framebuffer->bind();
    glClearColor(.117f, .564f, 1.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    Main::registry.each<Mesh>([&](const Entity& e)
                               {
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