// Copyright 2021 SMS
// License(Apache-2.0)
// 延迟渲染光照阶段

#version 450

#define DIRECTION_LIGHT_MAX 8
#define POINT_LIGHT_MAX     32
#define SPOT_LIGHT_MAX      32

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

    float constant;
    float linear;
    float quadratic;

    float cutOff;
    float outerCutOff;
};

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

layout(location = 0) out vec4 frag_color;

in vec2 v_uv;

uniform int            u_direction_lights_size;
uniform DirectionLight u_direction_lights[DIRECTION_LIGHT_MAX];
uniform int            u_point_lights_size;
uniform PointLight     u_point_lights[POINT_LIGHT_MAX];
uniform int            u_spot_lights_size;
uniform SpotLight      u_spot_lights[SPOT_LIGHT_MAX];

uniform sampler2D u_position;
uniform sampler2D u_normal;
uniform sampler2D u_albedo_spec;
uniform Material  u_material;
uniform vec3      u_dir_to_cam;

vec4 CalcLighting(vec3 position, vec3 normal, vec3 albedo);

void main()
{
    vec3  position = texture(u_position, v_uv).rgb;
    vec3  normal   = texture(u_normal, v_uv).rgb;
    vec3  albedo   = texture(u_albedo_spec, v_uv).rgb;
    float specular = texture(u_albedo_spec, v_uv).r;

    frag_color = CalcLighting(position, normal, albedo);
}

// 计算平行光照
vec3 CalcDirLight(DirectionLight light, vec3 normal)
{
    const vec3 dir_to_light = normalize(-light.direction);
    const vec3 albedo       = texture(u_material.albedo, v_uv).rgb;

    // 环境光照
    const vec3 ka      = u_material.ambient * vec3(light.intesity);
    const vec3 ambient = ka * light.color * albedo;

    // 漫反射光照
    const vec3  kd             = u_material.diffuse * vec3(light.intesity);
    const float diffuse_amount = max(dot(dir_to_light, normal), 0.0);
    const vec3  diffuse        = kd * light.color * diffuse_amount * albedo;

    // 镜面反射光照
    float shininess = 1.0 - texture(u_material.roughness, v_uv).r;
    if(shininess == 0.0)
        shininess = u_material.shininess;

    // const vec3  ks              = u_material.specular * vec3(light.intesity);
    const vec3  ks              = vec3(texture(u_material.metallic, v_uv).r) * vec3(light.intesity);
    const vec3  specular_color  = light.color;
    const vec3  reflected_dir   = reflect(-dir_to_light, normal);
    const float specular_amount = pow(max(dot(reflected_dir, v_dir_to_cam), 0.0), shininess);
    const vec3  specular        = ks * light.color * specular_amount * specular_color;

    // 放射光
    const vec3 emissive = u_material.emission * texture(u_material.emissive, v_uv).rgb;

    return ambient + diffuse + specular + emissive;
}

// 计算点光源光照
vec3 CalcPointLight(PointLight light, vec3 position, vec3 normal)
{
    const vec3 dir_to_light = normalize(light.position - position);

    // 衰减率
    const float distance    = length(light.position - position);
    const float attenuation = light.intesity / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    DirectionLight dirLight;
    dirLight.color     = light.color;
    dirLight.intesity  = light.intesity;
    dirLight.direction = -dir_to_light;
    return CalcDirLight(dirLight, normal) * attenuation;
}

// 计算聚光灯光照
vec3 CaclSpotLight(SpotLight light, vec3 position, vec3 normal)
{
    const vec3 dir_to_light = normalize(light.position - position);

    const float theta     = dot(dir_to_light, normalize(-light.direction)); 
    const float epsilon   = light.cutOff - light.outerCutOff;
    const float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    PointLight pointLight;
    pointLight.color     = light.color;
    pointLight.intesity  = light.intesity;
    pointLight.position  = light.position;
    pointLight.constant  = light.constant;
    pointLight.linear    = light.linear;
    pointLight.quadratic = light.quadratic;

    return CalcPointLight(pointLight, position, normal) * intensity;
}

// 计算总光照
vec4 CalcLighting(vec3 position, vec3 normal, vec3 albedo)
{
    vec3 light;
    for(int i = 0; i < u_direction_lights_size; ++i)
        light += CalcDirLight(u_direction_lights[i], normal);
    for(int i = 0; i < u_point_lights_size; ++i)
        light += CalcPointLight(u_point_lights[i], position, normal);
    for(int i = 0; i < u_spot_lights_size; ++i)
        light += CaclSpotLight(u_spot_lights[i], position, normal);
    return vec4(light, 1.0);
}