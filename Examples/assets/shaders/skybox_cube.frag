// Copyright 2021 SMS
// License(Apache-2.0)
// 盒型天空盒着色器

#version 450

out vec4 frag_color;

in vec3 v_uvw;

uniform samplerCube u_skybox;

void main()
{
  frag_color = texture(u_skybox, v_uvw);
}