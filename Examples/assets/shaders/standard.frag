// Copyright 2021 SMS
// License(Apache-2.0)

#version 450

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
    vec3  ambient;
    vec3  diffuse;
    vec3  specular;
    float shininess;
};

layout (location = 0) out vec4 frag_color;
layout (location = 1) out vec4 bright_color;
layout (location = 2) out int  entity_id;

in vec3 v_position;
in vec3 v_color;
in vec3 v_normal;
in vec2 v_uv;
in vec3 v_dir_to_cam;

#define DIRECTION_LIGHT_MAX 1
#define POINT_LIGHT_MAX     1

uniform int            u_direction_lights_size;
uniform DirectionLight u_direction_lights[DIRECTION_LIGHT_MAX];
uniform int            u_point_lights_size;
uniform PointLight     u_point_lights[POINT_LIGHT_MAX];

uniform Material  u_material;
uniform sampler2D u_texture;
uniform int       u_entity_id;

vec4 CalcLighting();

void main()
{
    // frag_color = vec4(1.0, 1.0, 1.0, 1.0) * CalcLighting();
    frag_color = texture(u_texture, vec2(1.0 - v_uv.x, 1.0 - v_uv.y)) * CalcLighting();

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

    const float ka = 1.0 * light.intesity;
    const float kd = 1.0 * light.intesity;
    const float ks = 1.0 * light.intesity;

    // 环境光照
    vec3 ambient = ka * light.color * u_material.ambient;

    // 漫反射光照
    float diffuse_amount = max(dot(dir_to_light, v_normal), 0.0);
    vec3  diffuse        = kd * light.color * diffuse_amount * u_material.diffuse;

    // 镜面反射光照
    vec3  reflected_direction = reflect(dir_to_light, v_normal);
    float specular_amount     = pow(max(dot(reflected_direction, v_dir_to_cam), 0.0), u_material.shininess);
    vec3  specular            = ks * light.color * specular_amount * u_material.specular;

    return ambient + diffuse + specular;
}

// 计算点光源光照
vec3 CalcPointLight(PointLight light)
{
    vec3 dir_to_light = normalize(light.position - v_position);

    // FIXME: 临时调试用
    light.constant  = 1.0f;
    light.linear    = 0.09;
    light.quadratic = 0.032;

    // 衰减率
    float distance    = length(light.position - v_position);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    DirectionLight dirLight;
    dirLight.color     = light.color;
    dirLight.intesity  = light.intesity;
    dirLight.direction = -dir_to_light;
    return CalcDirLight(dirLight) * attenuation;
}

// 计算总光照
vec4 CalcLighting()
{
    vec3 light;
    for(int i = 0; i < u_direction_lights_size; ++i)
         light += CalcDirLight(u_direction_lights[i]);
    for(int i = 0; i < u_point_lights_size; ++i)
        light += CalcPointLight(u_point_lights[i]);
    return vec4(light, 1.0);
}

/*
struct Material
{
    sampler2D diffuse;
    sampler2D specular;
    float     shininess;
};

vec4 CalcDirLight(DirectionLight light, vec3 normal, vec3 direction_to_cam)
{
    vec3 direction_to_light = normalize(-light.direction);

    // 环境光照
    vec3 ambient = light.ambient * vec3(texture(u_material.diffuse, v_uv));

    // 漫反射光照
    float diffuse_amount = max(0.0, dot(direction_to_light, v_normal));
    vec3  diffuse        = light.diffuse * diffuse_amount * vec3(texture(u_material.diffuse, v_uv));

    // 镜面反射光照
    vec3  reflected_direction = reflect(direction_to_light, v_normal);
    float specular_amount     = pow(max(0.0, dot(reflected_light, direction_to_cam)), u_material.shininess);
    vec3  specular            = light.specular * specular_amount * vec3(texture(u_material.specular, v_uv));
}
*/