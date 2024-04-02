//
//		File Name ： DeathCamera.cpp
//		Production： 2023/6/09
//		Author　　： 石田 恭一	
// 
//		ゲームカメラの実装を行ったクラス
//
//////////////////////////////////////////////////////////////////////////
//						Cameraのクラス									// 
//////////////////////////////////////////////////////////////////////////
#include "pch.h"
#include "DeathCamera.h"

// 注視点への距離の差分に対する割合・フェード
const float DeathCamera::FADE_RATE = 0.018f;

/// <summary>
/// コンストラクタ
/// </summary>
DeathCamera::DeathCamera()
{
}

/// <summary>
/// デストラクタ
/// </summary>
DeathCamera::~DeathCamera()
{
}

/// <summary>
/// 入れ替わる前に呼び出す
/// </summary>
/// <param name="finiteStateMachine">オーナー</param>
void DeathCamera::Enter(Camera::CAMERASTATE* finiteStateMachine)
{
	//	デスカメラに入った
	finiteStateMachine->GetOwner()->InDeathCamera();
}

/// <summary>
/// 実行する
/// </summary>
/// <param name="finiteStateMachine">オーナー<</param>
/// <param name="elapsedTime">経過時間</param>
void DeathCamera::Execute(Camera::CAMERASTATE* finiteStateMachine, const DX::StepTimer& timer)
{
	UNREFERENCED_PARAMETER(timer);
	//	親
	Camera* camera = finiteStateMachine->GetOwner();

	DirectX::SimpleMath::Vector3 target = finiteStateMachine->GetOwner()->GetOrijinalTargetPosition();
	target.y = -3.0f;

	//	追従させる
	camera->SetTargetPosition(DirectX::SimpleMath::Vector3::Lerp(camera->GetTargetPosition(), target, FADE_RATE));
	camera->SetEyePosition(DirectX::SimpleMath::Vector3::Lerp(camera->GetEyePosition(),		  target, FADE_RATE));
}

/// <summary>
/// 退出時の処理
/// </summary>
/// <param name="finiteStateMachine">オーナー</param>
void DeathCamera::Exit(Camera::CAMERASTATE* finiteStateMachine)
{
	UNREFERENCED_PARAMETER(finiteStateMachine);
}
