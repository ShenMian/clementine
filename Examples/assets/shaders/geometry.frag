// Copyright 2021 SMS
// License(Apache-2.0)
// 延迟渲染几何阶段

#version 450

struct Material
{
  vec3  ambient;
  vec3  diffuse;
  vec3  specular;
  vec3  emission;
  float shininess;
  
  sampler2D albedo;
  sampler2D metallic;
  sampler2D roughness;
  sampler2D ao;
  sampler2D emissive;
  sampler2D normal;
};

layout(location = 0) out vec3 position;
layout(location = 1) out vec3 normal;
layout(location = 2) out vec4 albedo_spec;

in vec3 v_position;
in vec3 v_normal;
in vec2 v_uv;

uniform Material u_material;

void main()
{
  position        = v_position;
  normal          = v_normal;
  albedo_spec.rbg = texture(u_material.albedo, v_uv).rgb;
  albedo_spec.a   = texture(u_material.metallic, v_uv).r;
}