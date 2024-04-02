//
//		File Name ： PlayerHPCrisisEffect.cpp
//		Production： 2023/1/10
//		Author　　： 石田 恭一	
//
#include "pch.h"
#include "PlayerHPCrisisEffect.h"


//	タイマーの加速
const float						   PlayerHPCrisisEffect::TIMER_SPEED				= 6.0f;
//	赤色の濃度	
const float						   PlayerHPCrisisEffect::RED_DENSITY				= 0.8f;
//	通常の大きさX
const float						   PlayerHPCrisisEffect::DEFAULT_SCALE_X			= 0.85f;
//	通常の大きさY
const float						   PlayerHPCrisisEffect::DEFAULT_SCALE_Y			= 0.82f;
//	拡大の補正値
const float						   PlayerHPCrisisEffect::CORRECTION_EXPANSION		= 0.01f;
//	ポストエフェクトの真ん中
const DirectX::SimpleMath::Vector2 PlayerHPCrisisEffect::CRISIS_ORIGIN_POSITION	= DirectX::SimpleMath::Vector2(794.0f, 444.0f);

/// <summary>
/// コンストラクタ
/// </summary>
PlayerHPCrisisEffect::PlayerHPCrisisEffect()
	:PostEffect(PostEffect::PostEffectType::PlayerHPCrisis)
{
}

/// <summary>
/// デストラクタ
/// </summary>
PlayerHPCrisisEffect::~PlayerHPCrisisEffect()
{
}

/// <summary>
/// 初期化処理
/// </summary>
void PlayerHPCrisisEffect::Initialize()
{
	m_texture = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"PinchEffect");
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="timer">タイマー</param>
void PlayerHPCrisisEffect::Update(const DX::StepTimer& timer)
{
	PostEffect::Update(timer);

	DirectX::SimpleMath::Color color = GetColor();

	//	赤を変える
	color.x = sinf(GetElapsedTime() * TIMER_SPEED) + RED_DENSITY;

	SetColor(color);

	//	拡大拡小する
	m_scale.x = DEFAULT_SCALE_X + sinf(GetElapsedTime() * TIMER_SPEED) * CORRECTION_EXPANSION;
	m_scale.y = DEFAULT_SCALE_Y + sinf(GetElapsedTime() * TIMER_SPEED) * CORRECTION_EXPANSION;
}

/// <summary>
/// 描画処理
/// </summary>
void PlayerHPCrisisEffect::Draw()
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
		m_scale
	);
}
