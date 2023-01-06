// Copyright 2021 SMS
// License(Apache-2.0)

#version 450
#extension GL_KHR_vulkan_glsl : enable
precision highp float;

const float PI = 3.14159265359;

struct Vert
{
	vec3 position;
	vec3 normal;
	vec2 tex_coord;
	vec3 tangent;
	vec3 bitangent;
	mat3 TBN;
};

struct DirectionalLight
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

layout(binding = 0) uniform Matrices
{
	mat4 view;
	mat4 proj;
	mat4 model;
} mat;

layout(binding = 1) uniform sampler2D albedo_map;
layout(binding = 2) uniform sampler2D normal_map;
layout(binding = 3) uniform sampler2D metallic_map;
layout(binding = 4) uniform sampler2D roughness_map;
layout(binding = 5) uniform sampler2D emissive_map;
layout(binding = 6) uniform sampler2D occlusion_map;

layout(binding = 7) uniform Material
{
	vec4  base_color_factor;
	vec4  emissive_factor;
	float metallic_factor;
	float roughness_factor;

	int albedo_map_set;
	int normal_map_set;
	int metallic_map_set;
	int roughness_map_set;
	int emissive_map_set;
	int occlusion_map_set;
	
	int workflow;
} matl;

layout(location = 0) in Vert vert;

layout(location = 0) out vec4 frag_color;

#define DEBUG_ONLY_ALBEDO    0
#define DEBUG_ONLY_NORMAL    0
#define DEBUG_ONLY_EMISSIVE  0
#define DEBUG_ONLY_METALNESS 0
#define DEBUG_ONLY_ROUGHNESS 0
#define DEBUG_ONLY_OCCLUSION 0

const int workflow_metallic_roughness = 0;
const int workflow_specular_glosiness = 1;

vec3 flat_normal(vec3 pos) {
	const vec3 fdx = dFdx(pos);
	const vec3 fdy = dFdy(pos);

	return normalize(cross(fdx, fdy));
}

/**
  * @brief 获取 TBN 矩阵.
  */
mat3 get_tbn_matrix()
{
	const vec3 q1  = dFdx(vert.position);
	const vec3 q2  = dFdy(vert.position);
	const vec2 st1 = dFdx(vert.tex_coord);
	const vec2 st2 = dFdy(vert.tex_coord);

	const vec3 N = normalize(vert.normal);
	const vec3 T = normalize(q1 * st2.t - q2 * st1.t);
	const vec3 B = -normalize(cross(N, T));
	return mat3(T, B, N);

	/*const vec3 T   = normalize(vec3(mat.model * vec4(vert.tangent,   0.0)));
    const vec3 B   = normalize(vec3(mat.model * vec4(vert.bitangent, 0.0)));
    const vec3 N   = normalize(vec3(mat.model * vec4(vert.normal,    0.0)));
    return transpose(mat3(T, B, N));*/
}

/**
  * @brief 获取向量.
  */
vec3 get_normal()
{
	const vec3 tangent_normal = normalize(texture(normal_map, vert.tex_coord).rgb * 2.0 - 1.0);
	const mat3 TBN            = get_tbn_matrix();

	return TBN * tangent_normal;
}

float distribution_GGX(vec3 N, vec3 H, float roughness)
{
    const float a  = roughness * roughness;
    const float a2 = a * a;
    const float NdotH  = max(dot(N, H), 0.0);
    const float NdotH2 = NdotH * NdotH;

    const float nom = a2;
    float denom     = (NdotH2 * (a2 - 1.0) + 1.0);
    denom           = PI * denom * denom;

    return nom / denom;
}

float geometry_schlick_GGX(float NdotV, float roughness)
{
    const float r = roughness + 1.0;
    const float k = (r * r) / 8.0;

    const float nom   = NdotV;
    const float denom = NdotV * (1.0 - k) + k;

    return nom / denom;
}

float geometry_smith(float NdotL, float NdotV, float roughness)
{
    return geometry_schlick_GGX(NdotL, roughness) * geometry_schlick_GGX(NdotV, roughness);
}

vec3 fresnel_schlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}

/**
  * @brief Cook-Torrance BRDF.
  */
vec3 BRDF(vec3 V, vec3 N, vec3 L)
{
	float metallic;
	float roughness;
	if(matl.workflow == workflow_metallic_roughness)
	{
		const vec4 color = texture(metallic_map, vert.tex_coord);
		metallic  = color.b;
		roughness = color.g;
	}
	else
	{
		// TODO
		roughness = 1.0 - texture(metallic_map, vert.tex_coord).a;
	}

	const vec3  albedo   = texture(albedo_map, vert.tex_coord).rgb;
	// const vec3  emissive = texture(emissive_map, vert.tex_coord).rgb;

	const vec3  H     = normalize(V + L);
	const float NdotL = max(dot(N, L), 0.0);
	const float NdotV = max(dot(N, V), 0.0);
	const float NdotH = max(dot(N, H), 0.0);

	vec3 F0 = vec3(0.04); 
    F0 = mix(F0, albedo, metallic);

	const float NDF = distribution_GGX(N, H, roughness);
    const float G   = geometry_smith(NdotL, NdotV, roughness);
    const vec3  F   = fresnel_schlick(clamp(NdotV, 0.0, 1.0), F0);
           
    const vec3  numerator   = NDF * G * F; 
    const float denominator = 4.0 * NdotV * NdotL + 0.0001; // + 0.0001 防止零除
    const vec3  specular    = numerator / denominator;

	vec3 ks = F;
    vec3 kd = vec3(1.0) - ks;
    kd *= 1.0 - metallic;

	// TODO
	const vec3 light_pos   = vec3(0.0);
	const vec3 light_color = vec3(3.0);

	float distance    = length(light_pos - vert.position);
    float attenuation = 1.0 / (distance * distance);
    // vec3  radiance    = light_color * attenuation;
    vec3  radiance    = light_color;

	return (kd * albedo / PI + specular) * radiance * NdotL;
}

void main()
{
	mat4 inv_view = inverse(mat.view);
	vec3 cam_pos  = inv_view[3].xyz;
	vec3 cam_dir  = -normalize(inv_view[2].xyz);

	const vec3 normal = get_normal();
	
	vec3 V = normalize(cam_pos - vert.position);
	vec3 L = normalize(vec3(-1.0, 0.0, -0.5));
	
	const vec4  albedo    = texture(albedo_map, vert.tex_coord);

	// TODO
	// const float occlusion = texture(occlusion_map, vert.tex_coord).r;
	// const float occlusion = texture(metallic_map, vert.tex_coord).r;
	const float occlusion = 1.0;

	const vec3 ambient = 0.3 * albedo.rgb;

	vec3 color = ambient + BRDF(V, normal, L);
	color      = color * occlusion;

	frag_color = vec4(color, albedo.a);

	if(matl.emissive_map_set == 1)
		frag_color.r = 1.0;

#if DEBUG_ONLY_ALBEDO
	frag_color.rgb = texture(albedo_map, vert.tex_coord).rgb;
#endif
#if DEBUG_ONLY_NORMAL
	frag_color.rgb = normal;
	frag_color.rgb = texture(normal_map, vert.tex_coord).rgb;
#endif
#if DEBUG_ONLY_EMISSIVE
	frag_color.rgb = texture(emissive_map, vert.tex_coord).rgb;
#endif
#if DEBUG_ONLY_METALNESS
	frag_color.rgb = vec3(texture(metallic_map, vert.tex_coord).r);
	frag_color.rgb = vec3(texture(metallic_map, vert.tex_coord).b);
#endif
#if DEBUG_ONLY_ROUGHNESS
	frag_color.rgb = vec3(texture(roughness_map, vert.tex_coord).r);
	frag_color.rgb = vec3(texture(roughness_map, vert.tex_coord).g);
#endif
#if DEBUG_ONLY_OCCLUSION
	frag_color.rgb = vec3(texture(occlusion_map, vert.tex_coord).r);
	frag_color.rgb = vec3(texture(metallic_map, vert.tex_coord).r);
#endif
	// frag_color = vec4(vert.tex_coord, 0.0, 1.0); // DEBUG: uv only
}
