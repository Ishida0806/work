//
//		File Name ： PlayerSwingSpeedEffect.cpp
//		Production： 2023/1/10
//		Author　　： 石田 恭一	
//
#include "pch.h"
#include "PlayerSwingSpeedEffect.h"


//	タイマーの加速
const float						   PlayerSwingSpeedEffect::TIMER_SPEED				= 7.0f;
//	ポストエフェクトの真ん中
const DirectX::SimpleMath::Vector2 PlayerSwingSpeedEffect::CRISIS_ORIGIN_POSITION	= DirectX::SimpleMath::Vector2(762.5f, 427.5);

/// <summary>
/// コンストラクタ
/// </summary>
PlayerSwingSpeedEffect::PlayerSwingSpeedEffect()
	:
	PostEffect(PostEffect::PostEffectType::SwingSpeedUP)
{
}

/// <summary>
/// デストラクタ
/// </summary>
PlayerSwingSpeedEffect::~PlayerSwingSpeedEffect()
{
}

/// <summary>
/// 初期化処理
/// </summary>
void PlayerSwingSpeedEffect::Initialize()
{
	m_texture = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"ColourlessBoard");
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="timer">タイマー</param>
void PlayerSwingSpeedEffect::Update(const DX::StepTimer& timer)
{
	PostEffect::Update(timer);

	DirectX::SimpleMath::Color color = GetColor();

	color.x = sinf(GetElapsedTime() * TIMER_SPEED);
	color.y = sinf(GetElapsedTime() * TIMER_SPEED);

	color.w = 0.0f;
	
	color.x = Utility::Clamp(color.x, 0.0f, 0.4f);
	color.y = Utility::Clamp(color.y, 0.0f, 0.4f);

	SetLerpColor(color);
}

/// <summary>
/// 描画処理
/// </summary>
void PlayerSwingSpeedEffect::Draw()
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
