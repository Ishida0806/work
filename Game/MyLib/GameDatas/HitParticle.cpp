
#include "pch.h"
#include "HitParticle.h"

/// <summary>
/// コンストラクタ
/// 引数は初期設定用の数値
/// </summary>
/// <param name="life">生存時間</param>
/// <param name="pos">座標</param>
/// <param name="velocity">速度</param>
/// <param name="accele">加速度</param>
/// <param name="startScale">初期サイズ</param>
/// <param name="endScale">最終サイズ</param>
/// <param name="startColor">初期色</param>
/// <param name="endColor">最終色</param>
HitParticle::HitParticle(
	float life, 
	DirectX::SimpleMath::Vector3 pos, 
	DirectX::SimpleMath::Vector3 velocity, 
	DirectX::SimpleMath::Vector3 accele, 
	DirectX::SimpleMath::Vector3 startScale, 
	DirectX::SimpleMath::Vector3 endScale, 
	DirectX::SimpleMath::Color startColor, 
	DirectX::SimpleMath::Color endColor
)
	:m_life(life),
	m_startLife(life),
	m_position(pos),
	m_velocity(velocity),
	m_memorryVelocity(velocity),
	m_accele(accele),
	m_memorryAcccele(accele),
	m_startScale(startScale),
	m_endScale(endScale),
	m_startColor(startColor),
	m_endColor(endColor)
{
	
}

/// <summary>
/// デストラクタ
/// </summary>
HitParticle::~HitParticle()
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="timer">タイマー</param>
void HitParticle::Update(const DX::StepTimer& timer)
{
	using namespace DirectX::SimpleMath;

	//処理に使う秒速計(1秒で1.0f)を取得する。
	float elapsedTime = static_cast<float>(timer.GetElapsedSeconds());

	float lerpSpeed = 0.1f;

	// スケール
	m_nowScale = Vector3::Lerp(m_nowScale, m_endScale, lerpSpeed);
	// 色
	m_nowColor = Color::Lerp(m_nowColor, m_endColor, lerpSpeed);
	// 速度の計算
	m_velocity += m_accele * elapsedTime;
	// 座標の計算
	m_position += m_velocity * elapsedTime;
	m_life -= elapsedTime;
}

/// <summary>
///  エフェクトを開始する
/// </summary>
/// <param name="position">座標</param>
void HitParticle::StartEffect(DirectX::SimpleMath::Vector3 position)
{
	m_life = m_startLife;

	m_position = position;
	m_velocity = m_memorryVelocity;
	m_accele   = m_memorryAcccele;

	m_nowScale = m_startScale;

	m_nowColor = m_startColor;
}
