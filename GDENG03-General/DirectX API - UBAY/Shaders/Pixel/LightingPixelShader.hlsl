Texture2D MyTexture : register(t0);
sampler Sampler : register(s0);

struct VS_TEXTURED_OUTPUT {
    float4 position : SV_POSITION;
    float2 textureCoordinate : TEXCOORD0;
    float3 normal : NORMAL0;
    float3 worldPosition : TEXCOORD1;
    float3 viewDirection : TEXCOORD2;
};
cbuffer MyConstant: register(b0) {
    row_major float4x4 world;
    row_major float4x4 view;
    row_major float4x4 projection;
    float time;
    float3 cameraPosition;
    float padding;
};

float4 main(VS_TEXTURED_OUTPUT input) : SV_TARGET {
    float4 textureColor = MyTexture.Sample(Sampler, input.textureCoordinate);

    float3 surfaceNormal = normalize(input.normal);
    float3 viewDirection = normalize(input.viewDirection);

    float3 totalDiffuse = float3(0.0f, 0.0f, 0.0f);
    float3 totalSpecular = float3(0.0f, 0.0f, 0.0f);

    float shininess = 32.0f;

    float3 directionalLightDirection = normalize(float3(
            cos(time * 0.3f), 
            -0.5f, 
            sin(time * 0.3f)));
    float3 directionalLightColor = float3(0.8f, 0.9f, 1.0f);
    float directionalLightIntensity = 1.5f;

    float directionalDiffuse = max(0.0f, dot(surfaceNormal, -directionalLightDirection));
    float3 directionalReflection = reflect(directionalLightDirection, surfaceNormal);
    float directionalSpecular = pow(max(0.0f, dot(viewDirection, directionalReflection)), shininess);

    totalDiffuse += directionalLightColor * directionalDiffuse * directionalLightIntensity;
    totalSpecular += directionalLightColor * directionalSpecular * directionalLightIntensity * 0.5f;

    float3 pointLightPosition = float3(
        sin(time * 1.5f) * 4.0f,
        2.0f,
        cos(time * 1.5f) * 2.0f);
    float3 pointLightColor = float3(1.0f, 0.6f, 0.3f);
    float pointLightIntensity = 6.0f;

    float3 pointLightVector = pointLightPosition - input.worldPosition;
    float pointLightDistance = length(pointLightVector);
    float3 pointLightDirection = normalize(pointLightVector);
    float pointDistanceAttenuation = 1.0f / (1.0f + 0.1f * pointLightDistance + 0.01f * pointLightDistance * pointLightDistance);

    float pointDiffuse = max(0.0f, dot(surfaceNormal, pointLightDirection));
    float3 pointReflection = reflect(-pointLightDirection, surfaceNormal);
    float pointSpecular = pow(max(0.0f, dot(viewDirection, pointReflection)), shininess);

    totalDiffuse += pointLightColor * pointDiffuse * pointLightIntensity * pointDistanceAttenuation;
    totalSpecular += pointLightColor * pointSpecular * pointLightIntensity * pointDistanceAttenuation * 0.8f;

    float3 spotLightPosition = float3(
        sin(time * 1.0f) * 3.0f,
        3.5f,
        cos(time * 1.0f) * 3.0f);
    float3 spotLightDirection = normalize(float3(0.0f, -1.0f, 0.0f));
    float3 spotLightColor = float3(0.9f, 0.9f, 1.0f);
    float spotLightIntensity = 8.0f;

    float3 spotLightVector = spotLightPosition - input.worldPosition;
    float spotLightDistance = length(spotLightVector);
    float3 spotLightDirectionToPixel = normalize(spotLightVector);
    float spotDistanceAttenuation = 1.0f / (1.0f + 0.05f * spotLightDistance + 0.01f * spotLightDistance * spotLightDistance);

    float spotAngle = dot(-spotLightDirectionToPixel, spotLightDirection);
    float innerConeAngle = cos(radians(12.0f));
    float outerConeAngle = cos(radians(25.0f));
    float spotFactor = smoothstep(outerConeAngle, innerConeAngle, spotAngle);

    float spotDiffuse = max(0.0f, dot(surfaceNormal, spotLightDirectionToPixel));
    float3 spotReflection = reflect(-spotLightDirectionToPixel, surfaceNormal);
    float spotSpecular = pow(max(0.0f, dot(viewDirection, spotReflection)), shininess);

    totalDiffuse += spotLightColor * spotDiffuse * spotLightIntensity * spotDistanceAttenuation * spotFactor;
    totalSpecular += spotLightColor * spotSpecular * spotLightIntensity * spotDistanceAttenuation * spotFactor;

    float3 ambientColor = float3(0.08f, 0.08f, 0.12f);

    float3 finalColor = textureColor.rgb * (ambientColor + totalDiffuse) + totalSpecular;

    return float4(finalColor, textureColor.a);
}