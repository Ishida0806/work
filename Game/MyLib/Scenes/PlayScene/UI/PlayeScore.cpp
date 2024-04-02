//
//		File Name ： PlayeScore.cpp
//		Production： 2023/11/27
//		Author　　： 石田 恭一
// 
#include "pch.h"
#include "PlayeScore.h"

#include "Game/MyLib/GameDatas/Number.h"
#include "Game/MyLib/GameDatas/PlayInfo.h"

//	数字の座標
static const DirectX::SimpleMath::Vector2 NUM_POSITION;
//	スコアの座標
static const DirectX::SimpleMath::Vector2 SCORE_POSITION;

/// <summary>
/// コンストラクタ
/// </summary>
PlayeScore::PlayeScore()
	:m_playInfo(nullptr),
	m_scoreBackGround(nullptr)
{
}

/// <summary>
/// デストラクタ
/// </summary>
PlayeScore::~PlayeScore()
{
}

/// <summary>
/// 初期化処理
/// </summary>
void PlayeScore::Initialize()
{
	// デバイス依存のリソースの初期化
	CreateDeviceDependentResources();
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="timer">タイマー</param>
void PlayeScore::Update(const DX::StepTimer& timer)
{
	timer;

	//	スコア表示を更新する
	m_scoreDisplay->Update(m_playInfo->GetScore());
}

/// <summary>
/// 描画処理
/// </summary>
void PlayeScore::Draw()
{
	//	スプライトバッチ
	DirectX::SpriteBatch* spriteBatch = MyLib::ScreenResources::GetInstance()->GetSpriteBatch();
	//	描画する
	spriteBatch->Draw
	(
		m_scoreBackGround,
		DirectX::SimpleMath::Vector2(153.0f,0.0f)
	);

	//	スコア表示
	m_scoreDisplay->Draw();
}

/// <summary>
/// 経過時間を止める
/// </summary>
void PlayeScore::StopElapsedTimer()
{
	//	経過時間を設定する
	m_playInfo->SetElapsedTime(MyLib::ElapsedTime::GetInstance()->GetElapsedTime());
}

/// <summary>
/// デバイス依存のリソースの初期化
/// </summary>
void PlayeScore::CreateDeviceDependentResources()
{
	//	プレイインフォメーションを作成する
	m_playInfo = PlayInfo::GetInstance();
	//	初期化を行う
	m_playInfo->Initialize();
	//	スコア表示
	m_scoreDisplay = std::make_unique<Number>
		(
			MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"number"),
			DirectX::SimpleMath::Vector2(315.0f, 12.5f)
		);

	//	スコアの画像
	m_scoreBackGround = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"PlayScoreBackGround");
}
