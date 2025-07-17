Texture2D MyTexture : register(t0);
sampler Sampler : register(s0);

struct VS_TEXTURED_OUTPUT {
    float4 position : SV_POSITION;
    float2 textureCoordinate : TEXCOORD0;
    float3 worldPos : TEXCOORD1;
    float3 worldNormal : TEXCOORD2;
};

struct MyLightData {
    float3 position;
    float range;
    float3 color;
    float intensity;
    float3 direction; // for directional / spot
    float spotAngle; // for spot
    int type; // 0 = directional, 1 = point, 2 = spot
    int enabled;
    float padding1;
    float padding2;
};

cbuffer MyConstant : register(b0) {
    row_major float4x4 world;
    row_major float4x4 view;
    row_major float4x4 projection;
    float time;
    int lightCount;
    float padding1;
    float padding2;
    MyLightData lights[16];
};

float4 main(VS_TEXTURED_OUTPUT input) : SV_TARGET {
    // MEMORY DUMP DIAGNOSTICS - Show exact raw values

    // Test 1: Show how many lights we have
    if (lightCount <= 0) {
        return float4(1.0, 0.0, 1.0, 1.0); // Bright magenta = no lights
    }

    // Show raw integer values more clearly
    float3 result = float3(0.0, 0.0, 0.0);

    // Check first light in detail
    if (lightCount >= 1) {
        int type0 = lights[0].type;
        int enabled0 = lights[0].enabled;

        // Show type as red intensity (should be 1 for point light)
        if (type0 == 1) {
            result.r = 1.0; // Correct point light
        } else if (type0 == 0) {
            result.r = 0.5; // Wrong - directional
        } else if (type0 == 2) {
            result.r = 0.3; // Wrong - spot
        } else {
            result.r = 0.1 + abs(float(type0)) * 0.05; // Show garbage value
        }

        // Show enabled status
        if (enabled0 == 0) {
            result.r = 0.0; // Disabled = black
        }
    }

    // Check second light (should be directional, type=0)
    if (lightCount >= 2) {
        int type1 = lights[1].type;
        int enabled1 = lights[1].enabled;

        if (type1 == 0) {
            result.g = 1.0; // Correct directional light
        } else if (type1 == 1) {
            result.g = 0.5; // Wrong - point
        } else if (type1 == 2) {
            result.g = 0.3; // Wrong - spot
        } else {
            result.g = 0.1 + abs(float(type1)) * 0.05; // Show garbage value
        }

        if (enabled1 == 0) {
            result.g = 0.0; // Disabled = black
        }
    }

    // Check third light (should be spot, type=2)
    if (lightCount >= 3) {
        int type2 = lights[2].type;
        int enabled2 = lights[2].enabled;

        if (type2 == 2) {
            result.b = 1.0; // Correct spot light
        } else if (type2 == 0) {
            result.b = 0.5; // Wrong - directional
        } else if (type2 == 1) {
            result.b = 0.3; // Wrong - point
        } else {
            result.b = 0.1 + abs(float(type2)) * 0.05; // Show garbage value
        }

        if (enabled2 == 0) {
            result.b = 0.0; // Disabled = black
        }
    }

    return float4(result, 1.0);
}
