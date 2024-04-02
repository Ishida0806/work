//
//		File Name ： Star.cpp
//		Production： 2023/11/02
//		Author　　： 石田 恭一
// 
//		夜空に浮かぶ星の描画更新を行う	
// 
#include "pch.h"
#include "Star.h"

#include "StageSelectScene.h"

//	星の画像の中央の座標
const DirectX::SimpleMath::Vector2	Star::ORIGIN_STAR_POSITION = DirectX::SimpleMath::Vector2(35.3f, 79.45);

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="starTexture">画像</param>
/// <param name="position">座標</param>
/// <param name="color">色</param>
/// <param name="scale">大きさ</param>
/// <param name="speed">速度</param>
/// <param name="lifeCount">生存時間</param>
Star::Star(
	ID3D11ShaderResourceView* starTexture,
	const DirectX::SimpleMath::Vector2& position,
	const DirectX::SimpleMath::Color& color, 
	const DirectX::SimpleMath::Vector2& scale,
	const float& speed,
	const float& lifeCount
) :m_starTexture(starTexture),
	m_position(position),
	m_memoryPosition(position),
	m_memoryColor(color),
	m_color(color),
	m_memoryScale(scale),
	m_scale(scale),
	m_speed(speed),
	m_lifeCount(lifeCount),
	m_memoryLifeCount(lifeCount),
	m_isUsed(false)
{
}

/// <summary>
/// デストラクタ
/// </summary>
Star::~Star()
{
}

/// <summary>
/// 初期化処理
/// </summary>
void Star::Initialize()
{
	//	最初は描画をしない
	m_lifeCount = 0.0f;
	m_isUsed = false;
	m_scale = DirectX::SimpleMath::Vector2::Zero;
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="timer">タイマー</param>
void Star::Update(const DX::StepTimer& timer)
{
	//	未使用状態なら生存時間を足す
	if (!m_isUsed) 
	{
		m_lifeCount += static_cast<float>(timer.GetElapsedSeconds());

		//	決められた生存時間を超えたら使用状態に
		if (m_lifeCount >= m_memoryLifeCount)
		{
			BeginStar();
		}
		else
		{
			return;
		}
	}

	//	生存時時間を減らす
	m_lifeCount -= static_cast<float>(timer.GetElapsedSeconds());

	//	スケールを段々と小さく
	m_scale = DirectX::SimpleMath::Vector2::Lerp(m_scale, DirectX::SimpleMath::Vector2::Zero, m_speed);

	//	生存時間が0になったら未使用状態に
	if (m_isUsed && m_lifeCount < 0.0f)
	{
		m_isUsed = false;
		m_scale = DirectX::SimpleMath::Vector2::Zero;
	}

}

/// <summary>
/// 描画する
/// </summary>
void Star::Draw()
{
	//	スプライトバッチ
	DirectX::SpriteBatch* spriteBatch = MyLib::ScreenResources::GetInstance()->GetSpriteBatch();

	//	描画行う
	spriteBatch->Draw
	(
		m_starTexture,
		m_position,
		nullptr,
		m_color,
		0.0f,
		ORIGIN_STAR_POSITION,
		m_scale
	);
}

/// <summary>
/// 終了処理
/// </summary>
void Star::Finalize()
{
}


/// <summary>
/// 開始する
/// </summary>
void Star::BeginStar()
{
	//	座標
	m_position  = m_memoryPosition;
	//	色
	m_color		= m_memoryColor;
	//	大きさ
	m_scale		= m_memoryScale;
	//	生存時間
	m_lifeCount = m_memoryLifeCount;
	//	使用状態
	m_isUsed	= true;
}