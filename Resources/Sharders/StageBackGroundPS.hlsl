      
cbuffer ConstBuffer : register(b1)
{
    float4 diffuse;
};


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
    // ‰æ‘œ•\Ž¦
    float4 ret = tex.Sample(samLinear, input.Tex);
    
    ret.r += diffuse.r;
    ret.g += diffuse.g;
    ret.b += diffuse.b;
    ret.a += diffuse.a;
    
    clamp(ret, 0.0f, 1.0f);
    
    return ret;
}