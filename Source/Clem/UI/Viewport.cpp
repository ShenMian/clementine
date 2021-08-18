// Copyright 2021 SMS
// License(Apache-2.0)

#include "Viewport.h"
#include "Browser.h"
#include "Rendering/OpenGL/GLFrameBuffer.h"
#include "Window/GlfwWindow.h"
#include <glad/glad.h>
#include <imgui/imgui.h>

namespace clem::ui
{

void Viewport::update(Time dt)
{
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{0, 0});
    ImGui::Begin("Viewport", &visible);
    ImGui::PopStyleVar();
    render(dt);
    ImGui::Image((ImTextureID) dynamic_cast<GLFrameBuffer*>(framebuffer.get())->colorAttachment, ImGui::GetContentRegionAvail(), {0, 1}, {1, 0}); // FIXME

    if(ImGui::IsWindowFocused() && ImGui::IsWindowHovered())
        ;

    ImGui::End();
}

void Viewport::attach()
{
    skybox   = Shader::create(R"(
		#version 450

		layout(location = 0) in vec3 a_position;
		layout(location = 1) in vec3 a_color;
		layout(location = 3) in vec2 a_uv;

        uniform mat4 u_view;
        uniform mat4 u_projection;

        out vec3 v_position;
        out vec2 v_uv;

		void main()
		{
            v_uv = a_uv;
			gl_Position = u_projection * u_view * vec4(a_position, 1.0);
		}
	)",
                            R"(
		#version 450

        in vec3 v_position;
        in vec2 v_uv;

        uniform sampler2D u_skybox;

		void main()
		{
            gl_FragColor = texture(u_skybox, 1.0 - v_uv);
		}
	)");

    standard = Shader::create(R"(
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

        struct Material
        {
            vec3  ambient;
            vec3  diffuse;
            vec3  specular;
            float shininess;
        };

        in vec3 v_position;
        in vec3 v_color;
        in vec3 v_normal;
        in vec2 v_uv;

        in vec3 v_cam_position;

        uniform Light     u_light;
        uniform Material  u_material;
        uniform sampler2D u_texture;

        // 光照. Blinn-Phong 反射模型
        vec4 light()
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

		void main()
		{
            gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0) * light();
            // gl_FragColor = texture(u_texture, vec2(1.0 - v_uv.x, v_uv.y)) * light();
		}
	)");

#if 1
    camera.setDirection({0, 0, 20}, {0, 0, -1}, -Vector3::unit_y);
#else
    camera.setDirection({0, 0, 20}, {0, 0, 1}, -Vector3::unit_y);
#endif

    light.translate({0, 1, 20});

    texture = Texture2D::create("../assets/textures/wall.jpg");
    texture->bind();

    auto win = Main::getWindow();

#if 0
    win->onMouseMove = [this](double x, double y)
    {
        static auto last  = getSize() / 2;
        static auto speed = Vector2::unit * 0.09;

        camera.view.rotateY(speed.x * radians(x - last.x));
        camera.view.rotateX(speed.y * radians(last.y - y));
        last = Vector2(x, y);
    };
#endif

    win->onScroll = [this](double xOfffset, double yOffset)
    {
        camera.view.scale(Vector3(1 + 0.1 * yOffset, 1 + 0.1 * yOffset, 1 + 0.1 * yOffset));
    };

    win->onResize = [this](Size2 size)
    {
        onResize();
    };
}

void Viewport::render(Time dt)
{
    onResize();

    texture->bind();
    standard->uploadUniform("u_texture", 0);

    light.rotateY(radians(90) * dt.seconds());
    standard->uploadUniform("u_light.position", light.translation());
    standard->uploadUniform("u_light.ambient", Vector3::unit * 1.0);
    standard->uploadUniform("u_light.diffuse", Vector3::unit * 1.0);
    standard->uploadUniform("u_light.specular", Vector3::unit * 1.0);

    Material material = Material::silver;
    standard->uploadUniform("u_material.ambient", material.ambient);
    standard->uploadUniform("u_material.diffuse", material.diffuse);
    standard->uploadUniform("u_material.specular", material.specular);
    standard->uploadUniform("u_material.shininess", material.shininess);

    standard->uploadUniform("u_view", camera.getViewMatrix());
    standard->uploadUniform("u_projection", camera.getProjectionMatrix());
    standard->uploadUniform("u_view_projection", camera.getViewProjectionMatrix());

    framebuffer->bind();
    glClearColor(.117f, .564f, 1.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    Main::registry.each<Model>([&](const Entity& e)
                               { Renderer::get()->submit(e, standard); });
    framebuffer->unbind();
}

void Viewport::onResize()
{
    Size2 size = {ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y};
#if 1
    camera.setPerspective(radians(45), size.x / size.y, 0.1f, 100.f);
#else
    camera.setOrthographic(size.x / 20, size.y / 20, -100.f, 100.f);
#endif
}

} // namespace clem::ui