//
//		File Name ： ChangeEffectPlay.cpp
//		Production： 2023/1/17
//		Author　　： 石田 恭一	
//
#include "pch.h"
#include "ChangeEffectPlay.h"

//	フェードの時間
const float						   ChangeEffectPlay::PLAY_FADE_TIME			= 2.8f;
//	アルファの値の減る値
const float						   ChangeEffectPlay::DIMINISH_ALFA_VALUE	= 0.005f;
//	退出フェード時の補正値
const float						   ChangeEffectPlay::CORRECTION_OUT_FADE	= 0.42f;


/// <summary>
///コンストラクタ
/// </summary>
ChangeEffectPlay::ChangeEffectPlay()
	:ChangeEffect(ChangeEffect::ChangeSceneType::Play)
{
}

/// <summary>
/// デストラクタ
/// </summary>
ChangeEffectPlay::~ChangeEffectPlay()
{
}

/// <summary>
/// 初期化処理
/// </summary>
void ChangeEffectPlay::Initialize()
{
	//	画像の設定
	ChangeEffect::SetTexure(MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"BlackTexture"));
}

/// <summary>
/// そのシーンに遷移する
/// </summary>
void ChangeEffectPlay::ToChange()
{
	DirectX::SimpleMath::Color color = GetColor();

	//	アルファ値だけ少しづつへらす
	color.w -= DIMINISH_ALFA_VALUE;

	SetColor(color);

	if (GetColor().w < 0.0f)
	{
		FinishedChangeScene();
	}
}

/// <summary>
/// シーンを抜ける
/// </summary>
void ChangeEffectPlay::OutChange()
{
	DirectX::SimpleMath::Color color = GetColor();

	//	アルファ値をふやふや動かす
	color.w = sinf(GetElapsedTime() * CORRECTION_OUT_FADE);

	SetColor(color);

	if (GetElapsedTime() >= PLAY_FADE_TIME)
	{
		FinishedChangeScene();
	}
}

/// <summary>
/// エフェクトの描画
/// </summary>
void ChangeEffectPlay::Draw()
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
void ChangeEffectPlay::PreInitialize()
{
	if (GetChangeFadeType() == ChangeEffect::ChangeSceneFadeType::To)
	{
		DirectX::SimpleMath::Color color = GetColor();

		//	色の濃さを決める
		color.x = 1.0f;
		color.y = 1.0f;
		color.z = 1.0f;
		color.w = 0.8f;

		SetColor(color);
	}
}