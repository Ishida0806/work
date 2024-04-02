//
//		File Name ： Enemy2D.cpp
//		Production： 2023/10/25
//		Author　　： 石田 恭一	
// 
//		2d敵の描画・更新を行う
// 
#include "pch.h"
#include "Enemy2D.h"

//	生成数
const int Enemy2D::GENERATION_ENEMY2D = 35;
//	画像の真ん中
const DirectX::SimpleMath::Vector2 Enemy2D::ORIGIN_ENEMY2D_TEXTURE = DirectX::SimpleMath::Vector2(112.0f, 91.5f);

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="texture">画像</param>
/// <param name="position">座標</param>
Enemy2D::Enemy2D(ID3D11ShaderResourceView* texture, const DirectX::SimpleMath::Vector2& position)
	:m_enemy2DTexture(texture),
	m_enemy2DPos(position),
	m_randomDirection(0),
	m_angle(0.0f),
	m_randomScale(0.0f),
	m_randomSpeed(0.0f),
	m_randomShake(0.0f)
{
	//	揺れる方向
	if (rand() % 2 == 0)
	{
		m_randomDirection = -1;
	}
	else 
	{
		m_randomDirection = 1;
	}

	//	ランダムな速度
	m_randomSpeed = Utility::CreateRandom(0.2f, 0.5f);
	//	ランダムな大きさ
	m_randomScale = Utility::CreateRandom(0.1f, 0.5f);
	//	ランダムな揺れ幅
	m_randomShake = Utility::CreateRandom(10.0f, 15.0f);
}

/// <summary>
/// デストラクタ
/// </summary>
Enemy2D::~Enemy2D()
{
}

/// <summary>
/// 初期化処理
/// </summary>
void Enemy2D::Initialize()
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="timer">タイマー</param>
void Enemy2D::Update(const DX::StepTimer& timer)
{
	//	速度を足す
	m_enemy2DPos.y += m_randomSpeed;
	//	右に左に揺らす
	m_angle = (m_randomShake * m_randomDirection) * sinf(static_cast<float>(timer.GetTotalSeconds()) * 3.0f);
	//	画面外に行ったら上まで戻す
	if (m_enemy2DPos.y >= 765.0f)
		m_enemy2DPos.y = -45.0f;
}

/// <summary>
/// 描画する
/// </summary>
void Enemy2D::Draw()
{
	//	スプライトバッチ
	DirectX::SpriteBatch* spriteBatch = MyLib::ScreenResources::GetInstance()->GetSpriteBatch();

	//	描画行う
	spriteBatch->Draw
	(
		m_enemy2DTexture,
		m_enemy2DPos,
		nullptr,
		DirectX::Colors::White,
		DirectX::XMConvertToRadians(m_angle),
		ORIGIN_ENEMY2D_TEXTURE,
		DirectX::SimpleMath::Vector2(m_randomScale, m_randomScale)
	);
}

/// <summary>
/// デバイス依存のリソースの初期化
/// </summary>
void Enemy2D::CreateDeviceDependentResources()
{
	
}
