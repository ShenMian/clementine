// Copyright 2021 SMS
// License(Apache-2.0)

#version 450

#define DIRECTION_LIGHT_MAX 1
#define POINT_LIGHT_MAX     1
#define SPOT_LIGHT_MAX      1

struct DirectionLight
{
    vec3  color;
    float intesity;

    vec3 direction;
};

struct PointLight
{
    vec3  color;
    float intesity;

    vec3 position;

    float constant;
    float linear;
    float quadratic;
};

struct SpotLight
{
    vec3  color;
    float intesity;

    vec3 position;
    vec3 direction;

    float cutOff;
    float outerCutOff;

    float constant;
    float linear;
    float quadratic;
};

struct Material
{
    vec3      ambient;
    vec3      diffuse;
    vec3      specular;
    vec3      emission;
    float     shininess;

    sampler2D diffuse_tex;
    sampler2D specular_tex;
    sampler2D emission_tex;
};

layout (location = 0) out vec4 frag_color;
layout (location = 1) out vec4 bright_color;
layout (location = 2) out int  entity_id;

in vec3 v_position;
in vec3 v_color;
in vec3 v_normal;
in vec2 v_uv;
in vec3 v_dir_to_cam;

uniform int            u_direction_lights_size;
uniform DirectionLight u_direction_lights[DIRECTION_LIGHT_MAX];
uniform int            u_point_lights_size;
uniform PointLight     u_point_lights[POINT_LIGHT_MAX];
uniform int            u_spot_lights_size;
uniform SpotLight      u_spot_lights[SPOT_LIGHT_MAX];

uniform Material  u_material;
uniform int       u_entity_id;
uniform sampler2D u_shadow_map;

vec4 CalcLighting();
vec3 CalcShadow();

void main()
{
    frag_color = texture(u_material.diffuse_tex, v_uv) * CalcLighting();

    // 提取亮色
    float brightness = dot(frag_color.rgb, vec3(0.2126, 0.7152, 0.0722));
    if(brightness > 1.0)
        bright_color = vec4(frag_color.rgb, 1.0);

    entity_id = u_entity_id;
}

// 计算平行光照
vec3 CalcDirLight(DirectionLight light)
{
    const vec3 dir_to_light = normalize(-light.direction);

    const vec3 ka = vec3(0.5) + u_material.ambient * vec3(light.intesity);
    const vec3 kd = vec3(1.2) + u_material.diffuse * vec3(light.intesity);
    const vec3 ks = vec3(1.2) + u_material.specular * vec3(light.intesity);

    // const vec3 diffuse_color  = texture(u_material.diffuse_tex, v_uv).rgb;
    // const vec3 specular_color = texture(u_material.specular_tex, v_uv).rgb;
    const vec3 diffuse_color  = vec3(1.0);
    const vec3 specular_color = vec3(1.0);

    // 环境光照
    vec3 ambient = ka * light.color * diffuse_color;

    // 漫反射光照
    float diffuse_amount = max(dot(dir_to_light, v_normal), 0.0);
    vec3  diffuse        = kd * light.color * diffuse_amount * diffuse_color;

    // 镜面反射光照
    vec3  reflected_dir   = reflect(dir_to_light, v_normal);
    float specular_amount = pow(max(dot(reflected_dir, v_dir_to_cam), 0.0), u_material.shininess);
    vec3  specular        = ks * light.color * specular_amount * specular_color;

    // 放射光
    vec3 emission = u_material.emission * texture(u_material.emission_tex, v_uv).rgb;
    
    vec3 shadow = CalcShadow();

    return ambient + (shadow * (diffuse + specular)) + emission;
}

// 计算点光源光照
vec3 CalcPointLight(PointLight light)
{
    vec3 dir_to_light = normalize(light.position - v_position);

    // FIXME: 临时调试用
    light.constant  = 1.0;
    light.linear    = 0.09;
    light.quadratic = 0.032;

    // 衰减率
    float distance    = length(light.position - v_position);
    float attenuation = light.constant + light.linear * distance + light.quadratic * (distance * distance);

    DirectionLight dirLight;
    dirLight.color     = light.color;
    dirLight.intesity  = light.intesity;
    dirLight.direction = -dir_to_light;
    return CalcDirLight(dirLight) / attenuation;
}

// 计算聚光灯光照
vec3 CaclSpotLight(SpotLight light)
{
    return vec3(0.0);
}

// 计算总光照
vec4 CalcLighting()
{
    vec3 light;
    for(int i = 0; i < u_direction_lights_size; ++i)
        light += CalcDirLight(u_direction_lights[i]);
    for(int i = 0; i < u_point_lights_size; ++i)
        light += CalcPointLight(u_point_lights[i]);
    for(int i = 0; i < u_spot_lights_size; ++i)
        light += CaclSpotLight(u_spot_lights[i]);
    return vec4(light, 1.0);
}

// 计算阴影
vec3 CalcShadow()
{
    return vec3(1.0);
}