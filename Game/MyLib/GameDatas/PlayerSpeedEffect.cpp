//
//		File Name ： PlayerSpeedEffect.cpp
//		Production： 2023/1/10
//		Author　　： 石田 恭一	
//
#include "pch.h"
#include "PlayerSpeedEffect.h"


//	タイマーの加速
const float						   PlayerSpeedEffect::TIMER_SPEED				= 7.0f;
//	ポストエフェクトの真ん中
const DirectX::SimpleMath::Vector2 PlayerSpeedEffect::CRISIS_ORIGIN_POSITION	= DirectX::SimpleMath::Vector2(762.5f, 427.5);

/// <summary>
/// コンストラクタ
/// </summary>
PlayerSpeedEffect::PlayerSpeedEffect()
	:PostEffect(PostEffect::PostEffectType::SpeedUP)
{
}

/// <summary>
/// デストラクタ
/// </summary>
PlayerSpeedEffect::~PlayerSpeedEffect()
{
}

/// <summary>
/// 初期化処理
/// </summary>
void PlayerSpeedEffect::Initialize()
{
	m_texture = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"ColourlessBoard");
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="timer">タイマー</param>
void PlayerSpeedEffect::Update(const DX::StepTimer& timer)
{

	PostEffect::Update(timer);

	DirectX::SimpleMath::Color color = GetColor();

	color.z = sinf(GetElapsedTime() * TIMER_SPEED);

	color.w = 0.0f;
	
	color.z = Utility::Clamp(color.z, 0.0f, 0.4f);

	SetLerpColor(color);
}

/// <summary>
/// 描画処理
/// </summary>
void PlayerSpeedEffect::Draw()
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
