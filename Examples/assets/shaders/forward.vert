// Copyright 2021 SMS
// License(Apache-2.0)
// 正向渲染着色器

#version 450

uniform mat4 u_view_projection;
uniform mat4 u_view;
uniform mat4 u_projection;
uniform mat4 u_model;

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 color;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec2 uv;
layout (location = 4) in vec3 tangent;
layout (location = 5) in vec3 bitangent;

out vec3 v_pos;
out vec3 v_color;
out vec3 v_normal;
out vec2 v_uv;
out vec3 v_dir_to_cam;

void main()
{
  v_pos    = vec3(u_model * vec4(pos, 1.0));
  v_color  = color;
  v_normal = normalize(mat3(transpose(inverse(u_model))) * normal);
  v_uv     = uv;

  v_dir_to_cam = normalize(u_view[3].xyz - v_pos);

  gl_Position = u_projection * u_view * u_model * vec4(pos, 1.0);
}