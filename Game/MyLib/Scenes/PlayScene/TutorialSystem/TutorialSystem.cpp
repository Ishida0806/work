//
//		File Name ： TutorialSystem.cpp
//		Production： 2024/4/04
//		Author　　： 石田 恭一	
// 
//		チュートリアル処理の記述をまとめたクラス
//	
#include "pch.h"
#include "TutorialSystem.h"

#include "TutorialMovingMethod.h"
#include "TutorialKillEnemyMethod.h"
#include "TutorialWeponMethod.h"
#include "TutorialFinishMethod.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="playScene">プレイシーン</param>
/// <param name="enemyManager">敵マネージャ</param>
TutorialSystem::TutorialSystem(PlayScene* playScene, EnemyManager* enemyManager)
	:
	m_playScene(playScene),
	m_enemyManager(enemyManager)
{
}

/// <summary>
/// デストラクタ
/// </summary>
TutorialSystem::~TutorialSystem()
{
}

/// <summary>
/// 初期化処理
/// </summary>
void TutorialSystem::Initialize()
{
	//	有限ステートマシーンを作成
	m_fsm = std::make_unique<TUTORIALSTATE>(this);
	//	ステートの追加
	m_fsm->RegisterState(TutorialState::MovingMethod, new TutorialMovingMethod());
	m_fsm->RegisterState(TutorialState::KillEnemyMethod, new TutorialKillEnemyMethod());
	m_fsm->RegisterState(TutorialState::WeponMethod, new TutorialWeponMethod());
	m_fsm->RegisterState(TutorialState::FinishMethod, new TutorialFinishMethod());
	//	始めるステートを選ぶ
	m_fsm->Start(TutorialState::MovingMethod);
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="timer">タイマー</param>
void TutorialSystem::Update(const DX::StepTimer& timer)
{
	//	更新する
	m_fsm->Update(timer);
}

/// <summary>
/// 描画処理
/// </summary>
void TutorialSystem::Render()
{
}

/// <summary>
/// 終了処理
/// </summary>
void TutorialSystem::Finalize()
{
}

/// <summary>
/// チュートリアル案内画像の設定
/// </summary>
/// <param name="texture">画像</param>
inline void TutorialSystem::SetGuideTexture(ID3D11ShaderResourceView* texture)
{
	m_guideTutorialTexture = texture;
}