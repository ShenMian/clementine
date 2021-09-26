// Copyright 2021 SMS
// License(Apache-2.0)
// 延迟渲染几何阶段

#version 450

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_color;
layout(location = 2) in vec3 a_normal;
layout(location = 3) in vec2 a_uv;

out vec3 v_position;
out vec3 v_normal;
out vec2 v_uv;

uniform mat4 u_view_projection;
uniform mat4 u_view;
uniform mat4 u_projection;
uniform mat4 u_model;

void main()
{
  v_position = vec3(u_model * vec4(a_position, 1.0));
  v_normal   = normalize(mat3(transpose(inverse(u_model))) * a_normal);
  v_uv       = a_uv;

  gl_Position = u_projection * u_view * vec4(v_position, 1.0);
}