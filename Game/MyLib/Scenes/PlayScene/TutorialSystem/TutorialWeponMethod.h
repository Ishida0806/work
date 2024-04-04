//
//		File Name ： TutorialWeponMethod.h
//		Production： 2024/4/04
//		Author　　： 石田 恭一	
//
#pragma once
#include "Game/MyLib/Scenes/PlayScene/TutorialSystem/TutorialSystem.h"

class TutorialWeponMethod : public TutorialSystem::ITUTORIALSTATE
{
	//	定数
public:

	//	変数
private:

	

	//	関数
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	TutorialWeponMethod();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~TutorialWeponMethod();

	/// <summary>
	/// 入れ替わる前に呼び出す
	/// </summary>
	/// <param name="finiteStateMachine">オーナー</param>
	void Enter(TutorialSystem::TUTORIALSTATE* finiteStateMachine) override;

	/// <summary>
	/// 実行する
	/// </summary>
	/// <param name="finiteStateMachine">オーナー<</param>
	/// <param name="elapsedTime">経過時間</param>
	void Execute(TutorialSystem::TUTORIALSTATE* finiteStateMachine, const DX::StepTimer& timer) override;

	/// <summary>
	/// 退出時の処理
	/// </summary>
	/// <param name="finiteStateMachine">オーナー</param>
	void Exit(TutorialSystem::TUTORIALSTATE* finiteStateMachine) override;
};