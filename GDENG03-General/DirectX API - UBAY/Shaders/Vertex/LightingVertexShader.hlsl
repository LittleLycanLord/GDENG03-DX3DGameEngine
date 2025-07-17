cbuffer TransformBuffer : register(b0) {
    matrix worldMatrix;
    matrix viewMatrix;
    matrix projectionMatrix;
    float time;
    float3 padding;
}

struct VertexInput {
    float3 position : POSITION;
    float2 texCoord : TEXCOORD;
    float3 normal : NORMAL;
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

    float4 worldPositionVector = mul(float4(input.position, 1.0f), worldMatrix);
    output.worldPosition = worldPositionVector.xyz;

    float4 viewPosition = mul(worldPositionVector, viewMatrix);
    output.position = mul(viewPosition, projectionMatrix);

    output.normal = normalize(mul(input.normal, (float3x3)worldMatrix));

    output.texCoord = input.texCoord;

    float3 cameraWorldPosition = -mul(float4(0, 0, 0, 1), viewMatrix).xyz;
    output.viewDirection = normalize(cameraWorldPosition - output.worldPosition);

    return output;
}
