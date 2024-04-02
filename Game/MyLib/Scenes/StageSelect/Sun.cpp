//
//		File Name ： Sun.cpp
//		Production： 2023/11/25
//		Author　　： 石田 恭一	
//
#include "pch.h"
#include "Sun.h"

#include "StageSelectScene.h"

//	画像の真ん中
const DirectX::SimpleMath::Vector2  Sun::ORIGIN_SUN_TEXTURE = DirectX::SimpleMath::Vector2(205.0f, 205.0f);

/// <summary>
/// コンストラクタ
/// </summary>
Sun::Sun()
{
}

/// <summary>
/// デストラクタ
/// </summary>
Sun::~Sun()
{
}

/// <summary>
/// 初期化処理
/// </summary>
void Sun::Initialize()
{
	// デバイス依存のリソースの初期化
	CreateDeviceDependentResources();
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="timer">タイマー</param>
/// <param name="stageNum">ステージ番号/param>
void Sun::Update(const DX::StepTimer& timer, const int& stageNum)
{
	UNREFERENCED_PARAMETER(timer);

	m_stage = stageNum;

	//	ステージ型にキャスト
	StageSelectScene::CHOOSE_STAGE stageSelect = static_cast<StageSelectScene::CHOOSE_STAGE>(m_stage);
	//	ステージは　3 || 4　か?
	if (stageSelect != StageSelectScene::CHOOSE_STAGE::STAGE_3)		return;
}

/// <summary>
/// 描画する
/// </summary>
void Sun::Draw()
{
	//	ステージ型にキャスト
	StageSelectScene::CHOOSE_STAGE stageSelect = static_cast<StageSelectScene::CHOOSE_STAGE>(m_stage);
	//	ステージは　3　か?
	if (stageSelect != StageSelectScene::CHOOSE_STAGE::STAGE_3)		return;

	//	スプライトバッチ
	DirectX::SpriteBatch* spriteBatch = MyLib::ScreenResources::GetInstance()->GetSpriteBatch();
	//	描画を行う
	spriteBatch->Draw
	(
		m_sunTexture,
		m_position,
		nullptr,
		DirectX::Colors::White,
		0.0f,
		ORIGIN_SUN_TEXTURE,
		m_scale
	);
}

/// <summary>
/// デバイス依存のリソースの初期化
/// </summary>
void Sun::CreateDeviceDependentResources()
{
	//	画像
	m_sunTexture = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"sun");

	m_position = { 1200.0f, 0.0 };

	m_scale = { 1.5f, 1.5f };
}
