// Copyright 2021 SMS
// License(Apache-2.0)
// 正向渲染着色器

#version 450

const float PI =  3.141592654;

#define DIRECTION_LIGHT_MAX 4
#define POINT_LIGHT_MAX     16
#define SPOT_LIGHT_MAX      16

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

uniform int            u_direction_lights_size;
uniform DirectionLight u_direction_lights[DIRECTION_LIGHT_MAX];
uniform int            u_point_lights_size;
uniform PointLight     u_point_lights[POINT_LIGHT_MAX];
uniform int            u_spot_lights_size;
uniform SpotLight      u_spot_lights[SPOT_LIGHT_MAX];

uniform Material  u_material;
uniform int       u_entity_id;
uniform sampler2D u_shadow_map;

layout (location = 0) out vec4 frag_color;
layout (location = 1) out int  entity_id;

in Out
{
  vec3 world_pos;
  vec3 color;
  vec3 normal;
  vec2 uv;
  mat3 TBN;
} vert;

in vec3 v_dir_to_cam;

vec4 CalcLighting(vec3 normal);
vec3 BRDF();

void main()
{
    vec4 albedo = texture(u_material.albedo, vert.uv);

    if(albedo.a < 0.5)
		discard;

    vec3 normal = texture(u_material.normal, vert.uv).rgb;
    normal      = normalize(vert.normal * 2.0 - 1.0);
    normal      = normalize(vert.TBN * normal);
    
    frag_color = albedo * CalcLighting(vert.normal);

    // 泛光
    // 提取亮色
    // float brightness = dot(frag_color.rgb, vec3(0.2126, 0.7152, 0.0722));
    // if(brightness > 1.0)
    //     bright_color = vec4(frag_color.rgb, 1.0);

    entity_id = u_entity_id;
}

vec3 CalcShadow();

vec3 BRDF(vec3 albedo, vec3 normal, vec3 dir_to_light);
vec3 Blinn(vec3 albedo, DirectionLight light, vec3 dir_to_light, vec3 normal);

// 计算平行光照
vec3 CalcDirLight(DirectionLight light, vec3 normal)
{
    const vec3 dir_to_light = normalize(-light.direction);
    const vec3 albedo       = texture(u_material.albedo, vert.uv).rgb;

#if 1
    vec3 lighting = BRDF(albedo, normal, dir_to_light) * light.color * vec3(light.intesity);
#else
    vec3 lighting = Blinn(albedo, light, dir_to_light, normal);
#endif

    return lighting;
}

vec3 Blinn(vec3 albedo, DirectionLight light, vec3 dir_to_light, vec3 normal)
{
    // 环境光照
    const vec3 ka      = u_material.ambient * vec3(light.intesity);
    const vec3 ambient = ka * light.color * albedo;

    // 漫反射光照
    const vec3  kd             = u_material.diffuse * vec3(light.intesity);
    const float diffuse_amount = max(dot(dir_to_light, normal), 0.0);
    const vec3  diffuse        = kd * light.color * diffuse_amount * albedo;

    // 镜面反射光照
    float shininess = 1.0 - texture(u_material.roughness, vert.uv).r;
    if(shininess == 0.0)
        shininess = u_material.shininess;

    // const vec3  ks              = u_material.specular * vec3(light.intesity);
    const vec3  ks              = vec3(texture(u_material.metallic, vert.uv).r) * vec3(light.intesity);
    const vec3  specular_color  = light.color;
    const vec3  reflected_dir   = reflect(-dir_to_light, normal);
    const float specular_amount = pow(max(dot(reflected_dir, v_dir_to_cam), 0.0), shininess);
    const vec3  specular        = ks * light.color * specular_amount * specular_color;

    // 放射光
    const vec3 emissive = u_material.emission * texture(u_material.emissive, vert.uv).rgb;
    
    const vec3 shadow = CalcShadow();

    return ambient + (shadow * (diffuse + specular)) + emissive;
}

// 计算点光源光照
vec3 CalcPointLight(PointLight light, vec3 normal)
{
    const vec3 dir_to_light = normalize(light.position - vert.world_pos);

    // FIXME: 临时调试用
    light.constant  = 1.0;
    light.linear    = 0.09;
    light.quadratic = 0.032;

    // 衰减率
    const float distance    = length(light.position - vert.world_pos);
    const float attenuation = light.intesity / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    DirectionLight dirLight;
    dirLight.color     = light.color;
    dirLight.intesity  = light.intesity;
    dirLight.direction = -dir_to_light;
    return CalcDirLight(dirLight, normal) * attenuation;
}

// 计算聚光灯光照
vec3 CaclSpotLight(SpotLight light, vec3 normal)
{
    const vec3 dir_to_light = normalize(light.position - vert.world_pos);

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

    return CalcPointLight(pointLight, normal) * intensity;
}

// 计算总光照
vec4 CalcLighting(vec3 normal)
{
    vec3 light;
    for(int i = 0; i < u_direction_lights_size; ++i)
        light += CalcDirLight(u_direction_lights[i], normal);
    for(int i = 0; i < u_point_lights_size; ++i)
        light += CalcPointLight(u_point_lights[i], normal);
    for(int i = 0; i < u_spot_lights_size; ++i)
        light += CaclSpotLight(u_spot_lights[i], normal);
    return vec4(light, 1.0);
}

// 计算阴影
vec3 CalcShadow()
{
    return vec3(1.0);
}

////////////////////

vec3  SchlickFresnel(vec3 f0, float cosT);
float GeometricOcclusion(float a, float NdotV);
float NormalDistribution(float a, float NdotH);

// Cook-Torance microfacet BRDF
vec3 BRDF(vec3 albedo, vec3 normal, vec3 dir_to_light)
{
    vec3 light_dir = dir_to_light;
    vec3 cam_dir   = v_dir_to_cam;

    float roughness = 0.0;
    float metallic  = texture(u_material.metallic, vert.uv).r;

    // Compute color at normal incidence
    vec3 f0 = vec3(1.0 - 0.04);
    f0      = abs((1.0 - f0) / (1.0 + f0));
    f0      = f0 * f0;
    f0      = mix(f0, albedo, metallic);

    // Compute half vector and all scalar products
    vec3  halfVec = normalize(cam_dir + light_dir);
    float NdotL   = clamp(dot(normal, light_dir),  0.0,   1.0);
    float NdotV   = clamp(dot(normal, cam_dir),    0.001, 1.0);
    float NdotH   = clamp(dot(normal, halfVec),    0.001, 1.0);
    float LdotH   = clamp(dot(light_dir, halfVec), 0.0,   1.0);
    float VdotH   = clamp(dot(cam_dir, halfVec),   0.0,   1.0);

    float alpha = roughness * roughness;
    vec3  F     = SchlickFresnel(f0, VdotH);
    float G     = GeometricOcclusion(alpha, NdotV);
    float D     = NormalDistribution(alpha, NdotH);

    // Compute specular term and accumulate light
    vec3 specular = F * G * D / (4.0 * NdotV);
    
    vec3       Ka = u_material.ambient;
    const vec3 Ks = F;
    vec3       Kd = 1 - Ks;
    Kd *= 1.0 - metallic;

    // 填写默认值
    if(Ka == vec3(0.0))
        Ka = vec3(0.2);

    const vec3 ambient  = Ka * albedo;// * texture(u_material.ao, vert.uv).rgb;
    const vec3 diffuse  = albedo * NdotL;
    const vec3 emissive = u_material.emission * texture(u_material.emissive, vert.uv).rgb;

    return ambient + diffuse + specular + emissive;
}

// 菲涅尔方程
// f0   平面的基础反射率
// cosT 表面法向量n与观察方向v的点乘的结果
vec3 SchlickFresnel(vec3 f0, float cosT)
{
    return f0 + (1.0 - f0) * pow(1.0 - cosT, 5.0);
}

float GeometricOcclusion(float a, float NdotV)
{
    const float a2 = a * 2;
    return 2.0 * NdotV / (NdotV + sqrt(a2 + (1.0 - a2) * (NdotV * NdotV)));
}

float GeometrySchlickGGX(float NdotV, float k)
{
    return NdotV / (NdotV * (1.0 - k) + k);
}

// 几何函数
// k 粗糙度.
float GeometrySmith(vec3 N, vec3 V, vec3 L, float k)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    return GeometrySchlickGGX(NdotV, k) * GeometrySchlickGGX(NdotL, k);
}

// 正态分布 GGX
float NormalDistribution(float a, float NdotH)
{
    const float a2    = a * a;
    const float denom = NdotH * NdotH * (a2 - 1.0) + 1.0;
    return a2 / (PI * denom * denom);
}