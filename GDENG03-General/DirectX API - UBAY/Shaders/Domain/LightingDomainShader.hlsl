#define NUM_CONTROL_POINTS 3

struct HS_CONTROL_POINT_OUTPUT {
    float4 position : SV_POSITION;
    float2 textureCoordinate : TEXCOORD0;
    float3 normal : NORMAL0;
};

struct VS_TEXTURED_OUTPUT {
    float4 position : SV_POSITION;
    float2 textureCoordinate : TEXCOORD0;
    float3 normal : NORMAL0;
};

struct HS_CONSTANT_DATA_OUTPUT {
    float edges[3] : SV_TessFactor;
    float inside : SV_InsideTessFactor;
};

cbuffer MyConstant : register(b0) {
    row_major float4x4 world;
    row_major float4x4 view;
    row_major float4x4 projection;
    float time;
};

[domain("tri")]
VS_TEXTURED_OUTPUT main(HS_CONSTANT_DATA_OUTPUT input,
                        const OutputPatch<HS_CONTROL_POINT_OUTPUT, NUM_CONTROL_POINTS> patch,
                        float3 barycentricCoordinates : SV_DomainLocation)
{
    VS_TEXTURED_OUTPUT output;

    // Simple pass-through using first vertex (no interpolation since tessellation factor is 1.0)
    // When tessellation factor is 1.0, barycentric coordinates will be (1,0,0), (0,1,0), or (0,0,1)
    float3 bary = barycentricCoordinates;
    
    // Interpolate position
    output.position = patch[0].position * bary.x + patch[1].position * bary.y + patch[2].position * bary.z;
    
    // Interpolate texture coordinates
    output.textureCoordinate = patch[0].textureCoordinate * bary.x + patch[1].textureCoordinate * bary.y + patch[2].textureCoordinate * bary.z;
    
    // Interpolate normals
    output.normal = patch[0].normal * bary.x + patch[1].normal * bary.y + patch[2].normal * bary.z;

    return output;
}
