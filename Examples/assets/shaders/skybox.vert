// Copyright 2021 SMS
// License(Apache-2.0)

#version 450

layout(location = 0) in vec3 a_position;

uniform mat4 u_view;
uniform mat4 u_projection;

out vec3 v_uvw;

void main()
{
  v_uvw = a_position;
  vec4 pos = u_projection * mat4(mat3(u_view)) * vec4(a_position, 1.0);
  gl_Position = pos.xyww;
}