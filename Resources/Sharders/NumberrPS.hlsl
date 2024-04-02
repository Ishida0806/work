
struct PS_INPUT
{
    float4 Pos : SV_POSITION;
    float4 Color : COLOR;
    float2 Tex : TEXCOORD;
};

Texture2D tex : register(t0);
SamplerState samLinear : register(s0);

float4 main(PS_INPUT input) : SV_TARGET
{
    // ‰æ‘œ•\¦
    float4 output = tex.Sample(samLinear, input.Tex);
    
    // ‚¿‚å‚Á‚ÆÔ‚ğ”Z‚­
    return output + input.Color.r;
}
