cbuffer TransformBuffer : register(b0) {
    row_major matrix worldMatrix;
    row_major matrix viewMatrix;
    row_major matrix projectionMatrix;
    float time;
    float3 padding;
}

struct VertexInput {
    float3 position : POSITION;
    float3 normal : NORMAL;
    float2 texCoord : TEXCOORD;
};

struct VertexOutput {
    float4 position : SV_POSITION;
    float3 worldPosition : WORLD_POSITION;
    float3 normal : NORMAL;
    float2 texCoord : TEXCOORD;
    float3 viewDirection : VIEW_DIR;
};

VertexOutput main(VertexInput input) {
    VertexOutput output;

    // Transform to world space (using row_major matrix multiplication order)
    float4 worldPosition = mul(float4(input.position, 1.0f), worldMatrix);
    output.worldPosition = worldPosition.xyz;

    // Transform to view space
    float4 viewPosition = mul(worldPosition, viewMatrix);

    // Transform to projection space
    output.position = mul(viewPosition, projectionMatrix);

    // Transform normal to world space (without translation)
    output.normal = normalize(mul(input.normal, (float3x3)worldMatrix));

    // Pass through texture coordinates
    output.texCoord = input.texCoord;

    // Simplified view direction calculation for now
    // We'll calculate this properly in the pixel shader using camera position
    output.viewDirection = normalize(float3(0, 0, 1));

    return output;
}
