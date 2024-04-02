struct PS_INPUT
{
    float4 Color : COLOR;
    float2 Tex : TEXCOORD;
    float4 Pos : SV_POSITION;
};

Texture2D tex : register(t0);
SamplerState samLinear : register(s0);

float4 main(PS_INPUT input) : SV_TARGET
{
    float4 ret = tex.Sample(samLinear, input.Tex);

    return ret;

}