
#include "pch.h"
#include "TutorialKillEnemyMethod.h"
#include "Game/MyLib/Scenes/PlayScene/Object/Object.h"
#include "Game/MyLib/Scenes/PlayScene/Object/Enemy/EnemyManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
TutorialKillEnemyMethod::TutorialKillEnemyMethod()
{
}

/// <summary>
/// デストラクタ
/// </summary>
TutorialKillEnemyMethod::~TutorialKillEnemyMethod()
{
}

/// <summary>
/// 入れ替わる前に呼び出す
/// </summary>
/// <param name="finiteStateMachine">オーナー</param>
void TutorialKillEnemyMethod::Enter(TutorialSystem::TUTORIALSTATE* finiteStateMachine)
{
	//	通常敵の作成
	finiteStateMachine->GetOwner()->GetEnemyManager()->CreateEnemy(EnemyManager::EnemyType::NormalEnemy, 4, 1, 1);
}

/// <summary>
/// 実行する
/// </summary>
/// <param name="finiteStateMachine">オーナー<</param>
/// <param name="elapsedTime">経過時間</param>
void TutorialKillEnemyMethod::Execute(TutorialSystem::TUTORIALSTATE* finiteStateMachine, const DX::StepTimer& timer)
{
	UNREFERENCED_PARAMETER(timer);

	//	敵を倒したら次のステート
	if (finiteStateMachine->GetOwner()->GetEnemyManager()->GetEnemy().size() == 0)
	{
		//	次の画像ガイドを設定する
		finiteStateMachine->GetOwner()->SetGuideTexture(MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"TutorialGuide04"));
		//	次の状態を決める
		finiteStateMachine->RequestTransition(TutorialSystem::TutorialState::FinishMethod);
	}
}

/// <summary>
/// 退出時の処理
/// </summary>
/// <param name="finiteStateMachine">オーナー</param>
void TutorialKillEnemyMethod::Exit(TutorialSystem::TUTORIALSTATE* finiteStateMachine)
{
	UNREFERENCED_PARAMETER(finiteStateMachine);
}
