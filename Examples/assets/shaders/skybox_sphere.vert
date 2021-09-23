// Copyright 2021 SMS
// License(Apache-2.0)
// 球型天空盒着色器

#version 450

layout(location = 0) in vec3 a_position;
layout(location = 3) in vec2 a_uv;

uniform mat4 u_view;
uniform mat4 u_projection;

out vec2 v_uv;

void main()
{
  v_uv = a_uv;
  vec4 pos = u_projection * mat4(mat3(u_view)) * vec4(a_position, 1.0);
  gl_Position = pos.xyww;
}