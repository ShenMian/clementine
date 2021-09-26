// Copyright 2021 SMS
// License(Apache-2.0)
// 延迟渲染光照阶段

#version 450

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;

out vec2 v_uv;

void main()
{
  v_uv = uv;

  gl_Position = vec4(position, 1.0);
}