//
//		File Name ： PlaySceneWave.h
//		Production： 2024/1/23
//		Author　　： 石田 恭一	
// 
//		プレイシーンのウェーブ数を管理するクラス
//
#include "pch.h"
#include "PlaySceneWave.h"
#include "../PlayScene.h"
#include "Game/MyLib/Scenes/StageSelect/StageSelectScene.h"


	//	ウェーブの色情報
const DirectX::SimpleMath::Color PlaySceneWave::WAVE_COLOR	= DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 0.7f);

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="playScene">プレイシーン</param>
PlaySceneWave::PlaySceneWave(PlayScene* playScene)
	:
	m_playScene(playScene),
	m_waveDisplayTexture(nullptr),
	m_isFinalWave(false),
	m_currentWave(1),
	m_maxWave(0)
{
}

/// <summary>
/// デストラクタ
/// </summary>
PlaySceneWave::~PlaySceneWave()
{
}

/// <summary>
///	初期化する
/// </summary>
void PlaySceneWave::Initialize()
{
	//	敵のデータの作成
	std::unique_ptr<ButtleWave> enemyData = std::make_unique<ButtleWave>(m_playScene);
	//	敵のデータを取得する
	m_enemyDatas = enemyData->OpenMap();
	//	最大ステージ数を取得する
	m_maxWave = enemyData->GetMaxWave();
	//	ウェーブの下画像
	m_waveDisplayTexture = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"WaveDisplay");
	//	現在のウェーブ数の数字を作成
	m_currentNumber = std::make_unique<Number>
	(
		MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"number"),
		DirectX::SimpleMath::Vector2(705.0f, 112.5f),
		m_currentWave
	);
	//	最大ウェーブ数の数字を作成
	m_maxNumber		= std::make_unique<Number>
	(
		MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"number"),
		DirectX::SimpleMath::Vector2(746.0f, 152.5f),
		m_maxWave
	);
}

/// <summary>
/// 更新処理
/// </summary>
void PlaySceneWave::Update()
{
	//	ステージの型にキャスト
	StageSelectScene::CHOOSE_STAGE stage = static_cast<StageSelectScene::CHOOSE_STAGE>(m_playScene->GetWordLevel());
	//	最大ステージの場合は帰れ
	if (stage == StageSelectScene::CHOOSE_STAGE::STAGE_4)	return;
	//	最大ウェーブ数の更新
	m_maxNumber->Update(m_maxWave);
	//	現在のウェーブの更新
	m_currentNumber->Update(m_currentWave);

	if (m_maxWave == m_currentWave)
	{
		//	最終ウェーブになった
		m_isFinalWave = true;
	}

#ifdef _DEBUG
	if(MyLib::InputSystem::GetInstance()->GetKeyTracer()->pressed.F2){ m_isFinalWave = true; }
#endif // _DEBUG

}

/// <summary>
/// 描画する
/// </summary>
void PlaySceneWave::Draw()
{
	//	ステージの型にキャスト
	StageSelectScene::CHOOSE_STAGE stage = static_cast<StageSelectScene::CHOOSE_STAGE>(m_playScene->GetWordLevel());
	//	最大ステージの場合は帰れ
	if (stage == StageSelectScene::CHOOSE_STAGE::STAGE_4)	return;

	//	描画する
	MyLib::ScreenResources::GetInstance()->GetSpriteBatch()->Draw
	(
		m_waveDisplayTexture,
		DirectX::SimpleMath::Vector2(680.0f, 68.0f),
		nullptr,
		WAVE_COLOR,
		0.0f,
		DirectX::SimpleMath::Vector2(74.5f, 76.0f)
	);
	//	最大数字を描画する
	m_maxNumber->DrawWaveNumber();
	//	現在のウェーブを描画する
	m_currentNumber->DrawWaveNumber();
}

/// <summary>
/// 次のウェーブへ行く
/// </summary>
void PlaySceneWave::NextWave()
{
	m_currentWave++;
}

/// <summary>
/// スポーンした敵オブジェクトのデータを削除する
/// </summary>
void PlaySceneWave::DeleteSpawnedEnemyData()
{
	// 条件を満たす敵オブジェクトを削除
	m_enemyDatas.erase
	(
		std::remove_if
		(
			m_enemyDatas.begin(), m_enemyDatas.end(),
			[&](const EnemyData& enemyData)
			{
				return enemyData.spawnWave == m_currentWave;
			}
		),
		m_enemyDatas.end()
	);
}
