//
//		File Name ： ChangeEffectTitle.cpp
//		Production： 2023/1/17
//		Author　　： 石田 恭一	
//
#include "pch.h"
#include "ChangeEffectTitle.h"


//	フェードの時間
const float ChangeEffectTitle::TITLE_FADE_TIME = 3.2f;

/// <summary>
/// コンストラクタ
/// </summary>
ChangeEffectTitle::ChangeEffectTitle()
	:ChangeEffect(ChangeEffect::ChangeSceneType::Title)
{
}

/// <summary>
/// デストラクタ
/// </summary>
ChangeEffectTitle::~ChangeEffectTitle()
{
}

/// <summary>
/// 初期化処理
/// </summary>
void ChangeEffectTitle::Initialize()
{
	//	画像の設定
	ChangeEffect::SetTexure(MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"BlackTexture"));
}

/// <summary>
/// そのシーンに遷移する
/// </summary>
void ChangeEffectTitle::ToChange()
{
	DirectX::SimpleMath::Color color = GetColor();

	color.x = 1.0f;
	color.y = 1.0f;
	color.z = 1.0f;
	color.w = sinf(GetElapsedTime());

	SetColor(color);

	if (GetElapsedTime() >= TITLE_FADE_TIME)
	{
		FinishedChangeScene();
	}
}

/// <summary>
/// シーンを抜ける
/// </summary>
void ChangeEffectTitle::OutChange()
{
	DirectX::SimpleMath::Color color = GetColor();

	color.x = 1.0f;
	color.y = 1.0f;
	color.z = 1.0f;
	color.w = sinf(GetElapsedTime());

	SetColor(color);

	if (GetElapsedTime() >= TITLE_FADE_TIME)
	{
		FinishedChangeScene();
	}
}

/// <summary>
/// エフェクトの描画
/// </summary>
void ChangeEffectTitle::Draw()
{
	MyLib::ScreenResources::GetInstance()->GetSpriteBatch()->Draw
	(
		GetTexture(),
		DirectX::SimpleMath::Vector2::Zero,
		GetColor()
	);
}
