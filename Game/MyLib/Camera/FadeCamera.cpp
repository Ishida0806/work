//
//		File Name ： FadeCamera.cpp
//		Production： 2023/6/09
//		Author　　： 石田 恭一	
// 
//		ゲームカメラの実装を行ったクラス
//
//////////////////////////////////////////////////////////////////////////
//						Cameraのクラス									// 
//////////////////////////////////////////////////////////////////////////
#include "pch.h"
#include "FadeCamera.h"

// 注視点への距離の差分に対する割合・フェード
const float FadeCamera::FADE_RATE = 0.008f;

/// <summary>
/// コンストラクタ
/// </summary>
FadeCamera::FadeCamera()
{
}

/// <summary>
/// デストラクタ
/// </summary>
FadeCamera::~FadeCamera()
{
}

/// <summary>
/// 入れ替わる前に呼び出す
/// </summary>
/// <param name="finiteStateMachine">オーナー</param>
void FadeCamera::Enter(Camera::CAMERASTATE* finiteStateMachine)
{
	UNREFERENCED_PARAMETER(finiteStateMachine);
}

/// <summary>
/// 実行する
/// </summary>
/// <param name="finiteStateMachine">オーナー<</param>
/// <param name="elapsedTime">経過時間</param>
void FadeCamera::Execute(Camera::CAMERASTATE* finiteStateMachine, const DX::StepTimer& timer)
{
	UNREFERENCED_PARAMETER(timer);
	//	親
	Camera* camera = finiteStateMachine->GetOwner();

	DirectX::SimpleMath::Vector3 target = finiteStateMachine->GetOwner()->GetOrijinalTargetPosition();
	//	追従させる
	camera->SetTargetPosition(DirectX::SimpleMath::Vector3::Lerp(camera->GetTargetPosition(), target, FADE_RATE));
	camera->SetEyePosition(DirectX::SimpleMath::Vector3::Lerp(camera->GetEyePosition(), target, FADE_RATE));

	//	フェード状態が終わったら状態遷移
	if (!camera->IsFade())
	{
		//	変える
		finiteStateMachine->RequestTransition(Camera::CameraState::Idle);
	}
}

/// <summary>
/// 退出時の処理
/// </summary>
/// <param name="finiteStateMachine">オーナー</param>
void FadeCamera::Exit(Camera::CAMERASTATE* finiteStateMachine)
{
	UNREFERENCED_PARAMETER(finiteStateMachine);
}
