//
//		File Name ： FadeCamera.h
//		Production： 2023/9/07
//		Author　　： 石田 恭一	
//
#pragma once
#include "Game/MyLib/Camera/Camera.h"

class FadeCamera : public Camera::ICAMERASTATE
{
	//	定数
public:

	// 注視点への距離の差分に対する割合・フェード
	static const float FADE_RATE;

	//	変数
private:



	//	関数
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	FadeCamera();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~FadeCamera();

	/// <summary>
	/// 入れ替わる前に呼び出す
	/// </summary>
	/// <param name="finiteStateMachine">オーナー</param>
	void Enter(Camera::CAMERASTATE* finiteStateMachine) override;

	/// <summary>
	/// 実行する
	/// </summary>
	/// <param name="finiteStateMachine">オーナー<</param>
	/// <param name="elapsedTime">経過時間</param>
	void Execute(Camera::CAMERASTATE* finiteStateMachine, const DX::StepTimer& timer) override;

	/// <summary>
	/// 退出時の処理
	/// </summary>
	/// <param name="finiteStateMachine">オーナー</param>
	void Exit(Camera::CAMERASTATE* finiteStateMachine) override;
};