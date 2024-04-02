Texture2D texture0 : register(t0); // normal map
Texture2D texture1 : register(t1); // height map

cbuffer ConstantBuffer : register(b0) 
{
    float height;
}

struct VS_OUTPUT 
{
    float4 Pos : POSITION;
    float4 Color : COLOR0;
    float2 TextureCoord : TEXCOORD0;
    float3 EyeDirection : TEXCOORD1;
    float3 LightDirection : TEXCOORD2;
};

float4 main(VS_OUTPUT input) : COLOR
{
    float3 light = normalize(input.LightDirection);
    float3 eye = normalize(input.EyeDirection);
    float hScale = texture1.SampleLevel(samLiner, input.TextureCoord, 0).r * height;
    float2 hTexCoord = input.TextureCoord - hScale * eye.xy;
    float3 mNormal = (texture0.SampleLevel(samLiner, hTexCoord, 0) * 2.0 - 1.0).rgb;
    float3 halfLE = normalize(light + eye);
    float diffuse = saturate(dot(mNormal, light));
    float specular = pow(saturate(dot(mNormal, halfLE)), 100.0);
    float4 destColor = input.Color * float4(diffuse, diffuse, diffuse, 1.0) + float4(specular, specular, specular, 1.0);
    return destColor;
}