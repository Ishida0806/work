//
//		File Name ： IdleCamera.cpp
//		Production： 2023/6/09
//		Author　　： 石田 恭一	
// 
//		ゲームカメラの実装を行ったクラス
//
//////////////////////////////////////////////////////////////////////////
//						Cameraのクラス									// 
//////////////////////////////////////////////////////////////////////////
#include "pch.h"
#include "IdleCamera.h"

//	カメラの位置への距離に対する割合
const float IdleCamera::EYE_RATE = 0.03f;
//	注視点への距離に対する割合
const float IdleCamera::TARGET_RATE = 0.1f;

/// <summary>
/// コンストラクタ
/// </summary>
IdleCamera::IdleCamera()
{
}

/// <summary>
/// デストラクタ
/// </summary>
IdleCamera::~IdleCamera()
{
}

/// <summary>
/// 入れ替わる前に呼び出す
/// </summary>
/// <param name="finiteStateMachine">オーナー</param>
void IdleCamera::Enter(Camera::CAMERASTATE* finiteStateMachine)
{
	UNREFERENCED_PARAMETER(finiteStateMachine);
}

/// <summary>
/// 実行する
/// </summary>
/// <param name="finiteStateMachine">オーナー<</param>
/// <param name="elapsedTime">経過時間</param>
void IdleCamera::Execute(Camera::CAMERASTATE* finiteStateMachine, const DX::StepTimer& timer)
{
	UNREFERENCED_PARAMETER(timer);
	//	カメラを取得する
	Camera* camera = finiteStateMachine->GetOwner();

	//	ダメージモードなら揺らすモードに
	if (finiteStateMachine->GetOwner()->IsShake())
	{
		//	変える
		finiteStateMachine->RequestTransition(Camera::CameraState::Shake);
		//	モード変更が完了
		finiteStateMachine->GetOwner()->CompletedShake();
	}
	//	追従ターゲット
	DirectX::SimpleMath::Vector3 target = finiteStateMachine->GetOwner()->GetOrijinalTargetPosition();
	//	ターゲットの追従
	camera->SetTargetPosition(DirectX::SimpleMath::Vector3::Lerp(camera->GetTargetPosition(), target, TARGET_RATE));
	camera->SetEyePosition(DirectX::SimpleMath::Vector3::Lerp(camera->GetEyePosition(), target, EYE_RATE));
}

/// <summary>
/// 退出時の処理
/// </summary>
/// <param name="finiteStateMachine">オーナー</param>
void IdleCamera::Exit(Camera::CAMERASTATE* finiteStateMachine)
{
	UNREFERENCED_PARAMETER(finiteStateMachine);
}
