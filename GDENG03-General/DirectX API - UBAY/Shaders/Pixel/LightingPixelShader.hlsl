#define MAX_LIGHTS 32

#define LIGHT_TYPE_DIRECTIONAL 0
#define LIGHT_TYPE_POINT 1
#define LIGHT_TYPE_SPOT 2

struct LightData {
    float4 position;
    float4 direction;
    float4 color;
    int lightType;
    float intensity;
    float range;
    float padding;
};

cbuffer LightingBuffer : register(b1) {
    LightData lights[MAX_LIGHTS];
    int numDirectionalLights;
    int numPointLights;
    int numSpotLights;
    int totalActiveLights;
    float3 ambientLight;
    float ambientIntensity;
    float lightingPadding[8];
}

cbuffer TransformBuffer : register(b0) {
    matrix worldMatrix;
    matrix viewMatrix;
    matrix projectionMatrix;
    float time;
    float3 transformPadding;
}

Texture2D diffuseTexture : register(t0);
SamplerState textureSampler : register(s0);

struct PixelInput {
    float4 position : SV_POSITION;
    float3 worldPosition : WORLD_POSITION;
    float3 normal : NORMAL;
    float2 texCoord : TEXCOORD;
    float3 viewDirection : VIEW_DIR;
};

static const float materialShininess = 32.0f;
static const float3 materialSpecular = float3(0.5f, 0.5f, 0.5f);

float CalculateAttenuation(float distance, float constantAttenuation, float linearAttenuation, float quadraticAttenuation) {
    return 1.0f / (constantAttenuation + linearAttenuation * distance + quadraticAttenuation * distance * distance);
}

float3 CalculateDirectionalLight(LightData light, float3 normal, float3 viewDirection, float3 albedo) {
    float3 lightDirection = normalize(-light.direction.xyz);

    float normalDotLight = max(dot(normal, lightDirection), 0.0f);
    float3 diffuseColor = light.color.xyz * normalDotLight * light.intensity;

    float3 halfwayDirection = normalize(lightDirection + viewDirection);
    float normalDotHalfway = max(dot(normal, halfwayDirection), 0.0f);
    float specularPower = pow(normalDotHalfway, materialShininess);
    float3 specularColor = light.color.xyz * specularPower * materialSpecular * light.intensity;

    return (diffuseColor + specularColor) * albedo;
}

float3 CalculatePointLight(LightData light, float3 fragmentPosition, float3 normal, float3 viewDirection, float3 albedo) {
    float3 lightPosition = light.position.xyz;
    float3 lightDirection = normalize(lightPosition - fragmentPosition);
    float distance = length(lightPosition - fragmentPosition);

    if (distance > light.range) return float3(0, 0, 0);

    float attenuation = CalculateAttenuation(distance, 1.0f, 0.09f, 0.032f);

    float normalDotLight = max(dot(normal, lightDirection), 0.0f);
    float3 diffuseColor = light.color.xyz * normalDotLight * light.intensity;

    float3 halfwayDirection = normalize(lightDirection + viewDirection);
    float normalDotHalfway = max(dot(normal, halfwayDirection), 0.0f);
    float specularPower = pow(normalDotHalfway, materialShininess);
    float3 specularColor = light.color.xyz * specularPower * materialSpecular * light.intensity;

    return (diffuseColor + specularColor) * albedo * attenuation;
}

float3 CalculateSpotLight(LightData light, float3 fragmentPosition, float3 normal, float3 viewDirection, float3 albedo) {
    float3 lightPosition = light.position.xyz;
    float3 lightDirection = normalize(lightPosition - fragmentPosition);
    float distance = length(lightPosition - fragmentPosition);

    if (distance > light.range) return float3(0, 0, 0);

    float3 spotDirection = normalize(light.direction.xyz);
    float theta = dot(lightDirection, - spotDirection);

    float innerCone = light.color.w;
    float outerCone = light.direction.w;

    float epsilon = innerCone - outerCone;
    float intensity = clamp((theta - outerCone) / epsilon, 0.0f, 1.0f);

    if (intensity <= 0.0f) return float3(0, 0, 0);

    float attenuation = CalculateAttenuation(distance, 1.0f, 0.09f, 0.032f);

    float normalDotLight = max(dot(normal, lightDirection), 0.0f);
    float3 diffuseColor = light.color.xyz * normalDotLight * light.intensity;

    float3 halfwayDirection = normalize(lightDirection + viewDirection);
    float normalDotHalfway = max(dot(normal, halfwayDirection), 0.0f);
    float specularPower = pow(normalDotHalfway, materialShininess);
    float3 specularColor = light.color.xyz * specularPower * materialSpecular * light.intensity;

    return (diffuseColor + specularColor) * albedo * attenuation * intensity;
}

float4 main(PixelInput input) : SV_TARGET {
    float3 albedo = diffuseTexture.Sample(textureSampler, input.texCoord).rgb;

    float3 normal = normalize(input.normal);
    float3 viewDirection = normalize(input.viewDirection);

    float3 finalColor = ambientLight * ambientIntensity * albedo;

    for (int i = 0; i < totalActiveLights && i < MAX_LIGHTS; ++ i) {
        LightData light = lights[i];

        if (light.lightType == LIGHT_TYPE_DIRECTIONAL) {
            finalColor += CalculateDirectionalLight(light, normal, viewDirection, albedo);
        }
        else if (light.lightType == LIGHT_TYPE_POINT) {
            finalColor += CalculatePointLight(light, input.worldPosition, normal, viewDirection, albedo);
        }
        else if (light.lightType == LIGHT_TYPE_SPOT) {
            finalColor += CalculateSpotLight(light, input.worldPosition, normal, viewDirection, albedo);
        }
    }

    finalColor = saturate(finalColor);

    return float4(finalColor, 1.0f);
}
