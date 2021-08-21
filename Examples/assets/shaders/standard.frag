// Copyright 2021 SMS
// License(Apache-2.0)

#version 450

struct Light
{
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct DirectionLight
{
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight
{
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight
{
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
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

in vec3 v_cam_position;

uniform Light     u_light;
uniform Material  u_material;
uniform sampler2D u_texture;
uniform int       u_entity_id;

vec4 lighting();

void main()
{
    frag_color = vec4(1.0, 1.0, 1.0, 1.0) * lighting();
    // frag_color = texture(u_texture, vec2(1.0 - v_uv.x, v_uv.y)) * lighting();

    // 提取亮色
    float brightness = dot(frag_color.rgb, vec3(0.2126, 0.7152, 0.0722));
    if(brightness > 1.0)
        bright_color = vec4(frag_color.rgb, 1.0);

    entity_id = u_entity_id;
}

// 计算平行光照
vec3 CalcDirLight(DirectionLight light, vec3 normal, vec3 dir_to_cam)
{
    vec3 dir_to_light = normalize(-light.direction);

    // 环境光照
    vec3 ambient = light.ambient * u_material.ambient;

    // 漫反射光照
    float diffuse_amount = max(0.0, dot(dir_to_light, v_normal));
    vec3  diffuse        = light.diffuse * (diffuse_amount * u_material.diffuse);

    // 镜面反射光照
    vec3  reflected_direction = reflect(dir_to_light, v_normal);
    float specular_amount     = pow(max(0.0, dot(reflected_direction, dir_to_cam)), u_material.shininess);
    vec3  specular            = light.specular * (specular_amount * u_material.specular);

    return ambient + diffuse + specular;
}

// 计算点光源光照
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 dir_to_cam)
{
    vec3 dir_to_light = normalize(light.position - v_position);

    // 衰减率
    float distance    = length(light.position - v_position);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    return CalcDirLight(DirectionLight(-dir_to_light, light.ambient, light.diffuse, light.specular), normal, dir_to_cam) * attenuation;
}

// 计算总光照
vec4 CalcLighting()
{
    vec3 light;
    return vec4(light, 1.0);
}

vec4 lighting()
{
    vec3 direction_to_light = normalize(u_light.position - v_position);
    vec3 direction_to_cam   = normalize(v_position - v_cam_position);

    // 环境光照
    const vec3 ka            = u_material.ambient;
    const vec3 ia            = u_light.ambient;
    vec3       ambient_light = ka * ia;

    // 漫反射光照
    const vec3 kd                  = u_material.diffuse;
    const vec3 id                  = u_light.diffuse;
    float      amont_diffuse_light = max(0.0, dot(direction_to_light, v_normal));
    vec3       diffuse_light       = kd * amont_diffuse_light * id;

    // 镜面反射光照
    const vec3 ks                    = u_material.specular;
    const vec3 is                    = u_light.specular;
    vec3       reflected_light       = reflect(direction_to_light, v_normal);
    float      shininess             = u_material.shininess;
    float      amount_specular_light = pow(max(0.0, dot(reflected_light, direction_to_cam)), shininess);
    vec3       specular_light        = ks * amount_specular_light * is;

    return vec4(ambient_light + diffuse_light + specular_light, 1.0);
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