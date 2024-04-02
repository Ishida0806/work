//
//		File Name ： ChangeEffectResult.cpp
//		Production： 2023/1/17
//		Author　　： 石田 恭一	
//
#include "pch.h"
#include "ChangeEffectResult.h"

//	フェードの時間
const float						   ChangeEffectResult::RESULT_FADE_TIME = 5.6f;
//	退出フェード時の補正値
const float						   ChangeEffectResult::CORRECTION_OUT_FADE	= 0.6f;


/// <summary>
/// コンストラクタ
/// </summary>
ChangeEffectResult::ChangeEffectResult()
	:ChangeEffect(ChangeEffect::ChangeSceneType::Result)
{
}

/// <summary>
/// デストラクタ
/// </summary>
ChangeEffectResult::~ChangeEffectResult()
{
}

/// <summary>
/// 初期化処理
/// </summary>
void ChangeEffectResult::Initialize()
{
	//	画像の設定
	ChangeEffect::SetTexure(MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"BlackTexture"));
}

/// <summary>
/// そのシーンに遷移する
/// </summary>
void ChangeEffectResult::ToChange()
{
	if (GetElapsedTime() >= RESULT_FADE_TIME)
	{
		FinishedChangeScene();
	}
}

/// <summary>
/// シーンを抜ける
/// </summary>
void ChangeEffectResult::OutChange()
{
	DirectX::SimpleMath::Color color = GetColor();

	//	アルファ値をふやふや動かす
	color.w = sinf(GetElapsedTime() * CORRECTION_OUT_FADE);

	SetColor(color);

	if (GetElapsedTime() >= RESULT_FADE_TIME)
	{
		FinishedChangeScene();
	}
}

/// <summary>
/// エフェクトの描画
/// </summary>
void ChangeEffectResult::Draw()
{
	//	ドアの左側を表示
	MyLib::ScreenResources::GetInstance()->GetSpriteBatch()->Draw
	(
		GetTexture(),
		DirectX::SimpleMath::Vector2::Zero,
		GetColor()
	);
}

/// <summary>
/// 事前の初期化を行う
/// </summary>
void ChangeEffectResult::PreInitialize()
{

}