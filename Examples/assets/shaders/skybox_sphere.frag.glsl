// Copyright 2021 SMS
// License(Apache-2.0)
// 球型天空盒着色器

#version 450

out vec4 frag_color;

in vec2 v_uv;

uniform sampler2D u_skybox;

void main()
{
  frag_color = texture(u_skybox, v_uv);
}