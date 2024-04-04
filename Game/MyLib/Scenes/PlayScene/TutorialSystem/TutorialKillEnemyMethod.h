//
//		File Name ： TutorialKillEnemyMethod.h
//		Production： 2024/4/04
//		Author　　： 石田 恭一	
//
#pragma once
#include "Game/MyLib/Scenes/PlayScene/TutorialSystem/TutorialSystem.h"

class TutorialKillEnemyMethod : public TutorialSystem::ITUTORIALSTATE
{
	//	定数
public:

	//	変数
private:

	//	マウスを動かしたか判定をとる場所
	DirectX::SimpleMath::Vector2 m_beforeMousePosition;

	//	関数
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	TutorialKillEnemyMethod();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~TutorialKillEnemyMethod();

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