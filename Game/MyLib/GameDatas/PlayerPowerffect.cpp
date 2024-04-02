//
//		File Name ： PlayerPowerffect.cpp
//		Production： 2023/1/10
//		Author　　： 石田 恭一	
//
#include "pch.h"
#include "PlayerPowerffect.h"


//	タイマーの加速
const float						   PlayerPowerffect::TIMER_SPEED				= 7.0f;
//	ポストエフェクトの真ん中
const DirectX::SimpleMath::Vector2 PlayerPowerffect::CRISIS_ORIGIN_POSITION	= DirectX::SimpleMath::Vector2(762.5f, 427.5);

/// <summary>
/// コンストラクタ
/// </summary>
PlayerPowerffect::PlayerPowerffect()
	:PostEffect(PostEffect::PostEffectType::PowerUP)
{
}

/// <summary>
/// デストラクタ
/// </summary>
PlayerPowerffect::~PlayerPowerffect()
{
}

/// <summary>
/// 初期化処理
/// </summary>
void PlayerPowerffect::Initialize()
{
	m_texture = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"ColourlessBoard");
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="timer">タイマー</param>
void PlayerPowerffect::Update(const DX::StepTimer& timer)
{
	PostEffect::Update(timer);

	DirectX::SimpleMath::Color color = GetColor();
	//	増やしたり減らしたり
	color.x = sinf(GetElapsedTime() * TIMER_SPEED);
	//	アルファ値は固定
	color.w = 0.0f;
	//	カラーの上限値を決める
	color.x = Utility::Clamp(color.x, 0.0f, 0.6f);

	SetLerpColor(color);

}

/// <summary>
/// 描画処理
/// </summary>
void PlayerPowerffect::Draw()
{
	//	スプライトバッチ
	DirectX::SpriteBatch* spriteBatch = MyLib::ScreenResources::GetInstance()->GetSpriteBatch();

	spriteBatch->Draw
	(
		m_texture,
		DirectX::SimpleMath::Vector2(640.0f, 360.0f),
		nullptr,
		GetColor(),
		0.0f,
		CRISIS_ORIGIN_POSITION,
		DirectX::SimpleMath::Vector2::One
	);
}
