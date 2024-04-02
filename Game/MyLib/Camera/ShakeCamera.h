//
//		File Name ： ShakeCamera.h
//		Production： 2023/9/07
//		Author　　： 石田 恭一	
//
#pragma once
#include "Game/MyLib/Camera/Camera.h"

class ShakeCamera : public Camera::ICAMERASTATE
{
	//	定数
public:

	//	プレイヤーがダメージを受けた際に揺らす振れ幅
	static const float SHAKE_CAMERA;
	//	揺らす時間
	static const float SHAKE_TIME;
	// カメラの位置への距離に対する割合
	static const float EYE_RATE;
	// 注視点への距離の差分に対する割合
	static const float TARGET_RATE;

	//	変数
private:

	//	経過時間
	float m_elapsedTime;

	//	関数
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ShakeCamera();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ShakeCamera();

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