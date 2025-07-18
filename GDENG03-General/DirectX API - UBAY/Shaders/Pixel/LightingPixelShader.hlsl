Texture2D MyTexture : register(t0);
sampler Sampler : register(s0);

struct VS_TEXTURED_OUTPUT {
    float4 position : SV_POSITION;
    float2 textureCoordinate : TEXCOORD0;
    float3 normal : NORMAL0;
};
cbuffer MyConstant: register(b0) {
    row_major float4x4 world;
    row_major float4x4 view;
    row_major float4x4 projection;
    float time;
};

float4 main(VS_TEXTURED_OUTPUT input) : SV_TARGET {
    // Sample the texture
    float4 textureColor = MyTexture.Sample(Sampler, input.textureCoordinate);

    // Simple static light from the right side for testing
    float3 lightDirection = normalize(float3(1.0f, 0.0f, 0.0f)); // Light from right side

    // Calculate basic diffuse lighting
    float3 normal = normalize(input.normal);
    float diffuse = max(0.0f, dot(normal, -lightDirection));

    // Simple binary cutoff for testing - very dramatic shadows
    if (diffuse < 0.5f) {
        diffuse = 0.0f; // Completely black shadow
    } else {
        diffuse = 1.0f; // Full light
    }

    // No ambient - pure dramatic lighting
    float3 finalColor = textureColor.rgb * diffuse;

    return float4(finalColor, textureColor.a);
}