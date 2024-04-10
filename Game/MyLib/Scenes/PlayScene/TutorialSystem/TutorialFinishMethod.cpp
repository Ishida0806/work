
#include "pch.h"
#include "TutorialFinishMethod.h"

#include "Game/MyLib/Scenes/PlayScene/PlayScene.h"

//	目標終了時間
const float TutorialFinishMethod::FINISH_TARGET_SECONDS	= 3.4f;

/// <summary>
/// コンストラクタ
/// </summary>
TutorialFinishMethod::TutorialFinishMethod()
	:
	m_elapsedTime(0.0f)
{
}

/// <summary>
/// デストラクタ
/// </summary>
TutorialFinishMethod::~TutorialFinishMethod()
{
}

/// <summary>
/// 入れ替わる前に呼び出す
/// </summary>
/// <param name="finiteStateMachine">オーナー</param>
void TutorialFinishMethod::Enter(TutorialSystem::TUTORIALSTATE* finiteStateMachine)
{

}

/// <summary>
/// 実行する
/// </summary>
/// <param name="finiteStateMachine">オーナー<</param>
/// <param name="elapsedTime">経過時間</param>
void TutorialFinishMethod::Execute(TutorialSystem::TUTORIALSTATE* finiteStateMachine, const DX::StepTimer& timer)
{
	//	経過時間
	m_elapsedTime += static_cast<float>(timer.GetElapsedSeconds());

	if (m_elapsedTime >= FINISH_TARGET_SECONDS)
	{
		//	チュートリアル終了
		finiteStateMachine->GetOwner()->GetPlayScene()->FinishTutorial();
	}
}

/// <summary>
/// 退出時の処理
/// </summary>
/// <param name="finiteStateMachine">オーナー</param>
void TutorialFinishMethod::Exit(TutorialSystem::TUTORIALSTATE* finiteStateMachine)
{
	UNREFERENCED_PARAMETER(finiteStateMachine);
}
