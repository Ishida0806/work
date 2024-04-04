//
//		File Name ： TutorialWeponMethod.cpp
//		Production： 2024/4/04
//		Author　　： 石田 恭一	
// 
//		武器を振る操作説明
//
#include "pch.h"
#include "TutorialWeponMethod.h"

/// <summary>
/// コンストラクタ
/// </summary>
TutorialWeponMethod::TutorialWeponMethod()
{
}

/// <summary>
/// デストラクタ
/// </summary>
TutorialWeponMethod::~TutorialWeponMethod()
{
}

/// <summary>
/// 入れ替わる前に呼び出す
/// </summary>
/// <param name="finiteStateMachine">オーナー</param>
void TutorialWeponMethod::Enter(TutorialSystem::TUTORIALSTATE* finiteStateMachine)
{

}

/// <summary>
/// 実行する
/// </summary>
/// <param name="finiteStateMachine">オーナー<</param>
/// <param name="elapsedTime">経過時間</param>
void TutorialWeponMethod::Execute(TutorialSystem::TUTORIALSTATE* finiteStateMachine, const DX::StepTimer& timer)
{
	//	マウス
	auto mouse = MyLib::InputSystem::GetInstance()->GetStateTracker();

	if (mouse->leftButton)
	{
		//	次の画像ガイドを設定する
		finiteStateMachine->GetOwner()->SetGuideTexture(MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"TutorialGuide03"));
		//	次の状態を決める
		finiteStateMachine->RequestTransition(TutorialSystem::TutorialState::KillEnemyMethod);
	}	
}

/// <summary>
/// 退出時の処理
/// </summary>
/// <param name="finiteStateMachine">オーナー</param>
void TutorialWeponMethod::Exit(TutorialSystem::TUTORIALSTATE* finiteStateMachine)
{
}
