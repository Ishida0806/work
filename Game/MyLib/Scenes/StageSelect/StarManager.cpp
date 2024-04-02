//
//		File Name ： StarManager.cpp
//		Production： 2023/11/02
//		Author　　： 石田 恭一
// 
//		夜空に浮かぶ星たちの更新を行う
// 
#include "pch.h"
#include "StarManager.h"

#include "StageSelectScene.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="backGroundTexture">画像</param>
StarManager::StarManager(ID3D11ShaderResourceView* starTexture)
	:m_starTexture(starTexture),
	m_stage(0)
{
}

/// <summary>
/// デストラクタ
/// </summary>
StarManager::~StarManager()
{
}

/// <summary>
/// 初期化処理
/// </summary>
void StarManager::Initialize()
{
	for (int i = 0; i < 50; i++)
	{
		//	ランダムな座標
		DirectX::SimpleMath::Vector2 randomPosition = DirectX::SimpleMath::Vector2(Utility::CreateRandom(100.0f, 1155.0f), Utility::CreateRandom(100.0f, 175.0f));
		//	ランダムな大きさ
		DirectX::SimpleMath::Vector2 randomScale	= DirectX::SimpleMath::Vector2(Utility::CreateRandom(0.05f, 0.1f), Utility::CreateRandom(0.05f, 0.1f));
		//	製造時間
		float randomLifeCount							= Utility::CreateRandom(1.3f, 12.2f);
		//	速度
		float speed = Utility::CreateRandom(0.03f, 0.05f);
					
		//	星の要素を追加する
		m_stars.push_back
		(
			std::make_unique<Star>
			(
				m_starTexture,
				randomPosition,
				DirectX::SimpleMath::Vector4::One,
				randomScale,
				speed,
				randomLifeCount
			)
		);
		//	初期化する
		m_stars[i]->Initialize();
	}
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="timer">タイマー</param>
/// <param name="selectStage">ステージセレクトナンバー</param>
void StarManager::Update(const DX::StepTimer& timer, const int& selectStage)
{
	m_stage = selectStage;

	//	ステージ型にキャスト
	StageSelectScene::CHOOSE_STAGE stageSelect = static_cast<StageSelectScene::CHOOSE_STAGE>(m_stage);

	//	ステージ4以降は帰れ
	if (stageSelect != StageSelectScene::CHOOSE_STAGE::STAGE_4)	return;

	//	星を更新する
	for (const auto& star : m_stars) star->Update(timer);
}

/// <summary>
/// 描画する
/// </summary>
void StarManager::Draw()
{
	//	ステージ型にキャスト
	StageSelectScene::CHOOSE_STAGE stageSelect = static_cast<StageSelectScene::CHOOSE_STAGE>(m_stage);

	//	ステージ4以降は帰れ
	if (stageSelect != StageSelectScene::CHOOSE_STAGE::STAGE_4)	return;

	//	星を描画する
	for (const auto& star : m_stars)	star->Draw();
}

/// <summary>
/// 終了処理
/// </summary>
void StarManager::Finalize()
{
	//	星を終了処理を行う
	for (const auto& star : m_stars)		star->Finalize();
}
