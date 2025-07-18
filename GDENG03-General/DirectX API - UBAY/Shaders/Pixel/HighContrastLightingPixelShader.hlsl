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

    // Strong directional light from the side for maximum shadow contrast
    float lightAngle = time * 0.8f; // Faster rotation to see effect
    float3 lightDirection = normalize(float3(
            cos(lightAngle), 
            -0.5f, 
            sin(lightAngle))); // Side lighting for strong shadows

    float3 lightColor = float3(3.0f, 2.8f, 2.5f); // Very intense warm light

    // Calculate diffuse lighting
    float3 normal = normalize(input.normal);
    float dotProduct = dot(normal, -lightDirection);
    float diffuse = max(0.0f, dotProduct);

    // Create EXTREME contrast with toon-like shading
    float shadowThreshold = 0.4f;
    float lightThreshold = 0.7f;

    float shadingLevel;
    if (diffuse < shadowThreshold) {
        shadingLevel = 0.05f; // Deep shadow - almost black
    } else if (diffuse < lightThreshold) {
        shadingLevel = 0.3f; // Mid tone
    } else {
        shadingLevel = 1.0f; // Full light
    }

    // No ambient light at all - pure shadow areas are black
    float3 ambient = float3(0.0f, 0.0f, 0.0f);

    // Apply the dramatic lighting
    float3 finalColor = textureColor.rgb * (ambient + lightColor * shadingLevel);

    // Add edge highlighting for better visibility
    float edge = abs(dotProduct);
    if (edge > 0.8f) {
        finalColor += float3(0.2f, 0.2f, 0.1f); // Bright edge highlight
    }

    return float4(finalColor, textureColor.a);
}
