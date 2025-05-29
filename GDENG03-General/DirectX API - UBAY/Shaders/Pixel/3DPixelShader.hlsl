struct VS_ANIMATED_OUTPUT {
    float4 position : SV_POSITION;
    float3 color : COLOR;
    float3 nextColor : COLOR1;
};
cbuffer MyConstant: register(b0) {
    row_major float4x4 world;
    row_major float4x4 view;
    row_major float4x4 projection;
    float angle;
};
float4 main(VS_ANIMATED_OUTPUT input) : SV_TARGET {
    return float4(lerp(input.color, input.nextColor, (sin(angle) + 1.0f) / 2.0f), 1.0f);
}