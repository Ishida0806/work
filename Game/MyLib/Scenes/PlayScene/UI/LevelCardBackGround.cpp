
#include "pch.h"
#include "LevelCardBackGround.h"

//	背景画像の中心点
const DirectX::SimpleMath::Vector2 LevelCardBackGround::BACKGROUND_ORIGIN_POSITION	  = { 699.0f,370.0f };
//	背景画像の初期化Y座標
const float						   LevelCardBackGround::BACKGROUND_RESTART_POSITION_Y = -360.0f;
//	上に上がる速さ
const float						   LevelCardBackGround::EXIT_SPEED_POSITION_Y		  = 15.0f;
//	入場の速さ
const float						   LevelCardBackGround::IN_SPEED					  = 0.2f;
//	退場の速さ
const float						   LevelCardBackGround::EXIT_SPEED					  = 0.1f;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="player">プレイヤー</param>
LevelCardBackGround::LevelCardBackGround()
	:
	m_isClick(false),
	m_backGroundTexture(nullptr)
{
}

/// <summary>
/// デストラクタ
/// </summary>
LevelCardBackGround::~LevelCardBackGround()
{
}

/// <summary>
/// 初期化処理
/// </summary>
void LevelCardBackGround::Initialize()
{
	//	画像を取得
	m_backGroundTexture = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"leverUpCardBackGround");
	//	横、高さ
	int w, h;
	//	画面のサイズを取得する
	MyLib::ScreenResources::GetInstance()->GetScreenSize(w, h);
	//	画面の真ん中に出す
	m_backGroundTargetPosition = DirectX::SimpleMath::Vector2(static_cast<float>(w / 2.0f), static_cast<float>(h / 2.0f));
	// 座標の初期化
	ResetPosition();
	//	最初はゼロ
	m_backGroundScale = DirectX::SimpleMath::Vector2::Zero;
}

/// <summary>
/// 更新処理
/// </summary>
void LevelCardBackGround::Update()
{
	//	どんどん大きくする
	m_backGroundScale = DirectX::SimpleMath::Vector2::Lerp(m_backGroundScale, DirectX::SimpleMath::Vector2::One, IN_SPEED);

	m_backGroundPosition = DirectX::SimpleMath::Vector2::Lerp(m_backGroundPosition, m_backGroundTargetPosition, IN_SPEED);
}


/// <summary>
/// 退出処理
/// </summary>
void LevelCardBackGround::Exit()
{
	//	どんどん小さくする
	m_backGroundScale = DirectX::SimpleMath::Vector2::Lerp(m_backGroundScale, DirectX::SimpleMath::Vector2::Zero, EXIT_SPEED);

	m_backGroundPosition.y -= EXIT_SPEED_POSITION_Y;

	if (m_backGroundPosition.y <= BACKGROUND_RESTART_POSITION_Y)
	{
		// 座標の初期化
		ResetPosition();
	}
}

/// <summary>
/// 描画する
/// </summary>
void LevelCardBackGround::Draw()
{
	DirectX::SpriteBatch* spriteBatch = MyLib::ScreenResources::GetInstance()->GetSpriteBatch();

	spriteBatch->Draw
	(
		m_backGroundTexture,
		m_backGroundPosition,
		nullptr,
		DirectX::Colors::White,
		0.0f,
		BACKGROUND_ORIGIN_POSITION,
		m_backGroundScale
	);
}

/// <summary>
/// 座標の初期化
/// </summary>
void LevelCardBackGround::ResetPosition()
{
	//	X座標は同じ
	m_backGroundPosition.x = m_backGroundTargetPosition.x;
	//	Y座標の初期化
	m_backGroundPosition.y = BACKGROUND_RESTART_POSITION_Y;
}
