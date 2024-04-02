//
//		File Name ： Camera.cpp
//		Production： 2023/6/09
//		Author　　： 石田 恭一	
// 
//		ゲームカメラの実装を行ったクラス
//
//////////////////////////////////////////////////////////////////////////
//						Cameraのクラス							  // 
//////////////////////////////////////////////////////////////////////////
#include "pch.h"
#include "ShakeCamera.h"

//	プレイヤーがダメージを受けた際に揺らす振れ幅
const float ShakeCamera::SHAKE_CAMERA	  = 0.22f;
//	揺らす時間
const float ShakeCamera::SHAKE_TIME		  = 0.5f;
//	カメラの位置への距離に対する割合
const float ShakeCamera::EYE_RATE		  = 0.025f;
//	注視点への距離に対する割合
const float ShakeCamera::TARGET_RATE	  = 0.95f;

/// <summary>
/// コンストラクタ
/// </summary>
ShakeCamera::ShakeCamera()
	:m_elapsedTime(0.0f)
{
}

/// <summary>
/// デストラクタ
/// </summary>
ShakeCamera::~ShakeCamera()
{
}

/// <summary>
/// 入れ替わる前に呼び出す
/// </summary>
/// <param name="finiteStateMachine">オーナー</param>
void ShakeCamera::Enter(Camera::CAMERASTATE* finiteStateMachine)
{
	//	初期化
	m_elapsedTime = 0.0f;

	UNREFERENCED_PARAMETER(finiteStateMachine);
}

/// <summary>
/// 実行する
/// </summary>
/// <param name="finiteStateMachine">オーナー<</param>
/// <param name="elapsedTime">経過時間</param>
void ShakeCamera::Execute(Camera::CAMERASTATE* finiteStateMachine, const DX::StepTimer& timer)
{
	//	経過時間を足す
	m_elapsedTime += static_cast<float>(timer.GetElapsedSeconds());
	//	カメラ
	Camera* camera = finiteStateMachine->GetOwner();

	if (camera->IsShake())	
	{
		camera->CompletedShake();
		m_elapsedTime = 0.0f;
	}

	//	ターゲットを取得する
	DirectX::SimpleMath::Vector3 orijinalTarget = camera->GetOrijinalTargetPosition();
	//	ターゲットの追従
	camera->SetTargetPosition(DirectX::SimpleMath::Vector3::Lerp(camera->GetTargetPosition(), orijinalTarget, TARGET_RATE));
	camera->SetEyePosition(DirectX::SimpleMath::Vector3::Lerp(camera->GetEyePosition(),		  orijinalTarget, EYE_RATE));

	//	ターゲットを取得する
	DirectX::SimpleMath::Vector3 target = camera->GetTargetPosition();
	//	ターゲットを揺らす
	target.x += Utility::CreateRandom(-SHAKE_CAMERA, SHAKE_CAMERA);
	target.z += Utility::CreateRandom(-SHAKE_CAMERA, SHAKE_CAMERA);
	//	カメラを設定する
	camera->SetTargetPosition(target);

	if (m_elapsedTime > SHAKE_TIME)
	{
		//	変える
		finiteStateMachine->RequestTransition(Camera::CameraState::Idle);
	}
}

/// <summary>
/// 退出時の処理
/// </summary>
/// <param name="finiteStateMachine">オーナー</param>
void ShakeCamera::Exit(Camera::CAMERASTATE* finiteStateMachine)
{
	UNREFERENCED_PARAMETER(finiteStateMachine);
	//	初期化
	m_elapsedTime = 0.0f;
}
