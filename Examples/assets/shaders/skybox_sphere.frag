// Copyright 2021 SMS
// License(Apache-2.0)

#version 450

out vec4 frag_color;

in vec2 v_uv;

uniform sampler2D u_skybox;

void main()
{
  frag_color = texture(u_skybox, vec2(v_uv.x, 1.0 - v_uv.y));
}