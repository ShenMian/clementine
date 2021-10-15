// Copyright 2021 SMS
// License(Apache-2.0)
// 延迟渲染几何阶段

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
out vec3 v_normal;
out vec2 v_uv;

void main()
{
  vec3 T   = normalize(vec3(u_model * vec4(tangent,   0.0)));
  vec3 B   = normalize(vec3(u_model * vec4(bitangent, 0.0)));
  vec3 N   = normalize(vec3(u_model * vec4(normal,    0.0)));
  mat3 TBN = transpose(mat3(T, B, N));

  v_pos    = vec3(u_model * vec4(pos, 1.0));
  v_normal = normalize(mat3(transpose(inverse(u_model))) * normal);
  v_uv     = uv;

  gl_Position = u_projection * u_view * vec4(v_pos, 1.0);
}