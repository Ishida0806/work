#include "Particle.hlsli"

Texture2D tex : register(t0);
SamplerState samLinear : register(s0);

float4 main(PS_INPUT input) : SV_TARGET
{
    // 画像表示
    float4 output = tex.Sample(samLinear, input.Tex);
    
     //    ちょっと赤を濃く
    return output + input.Color.r;
}
