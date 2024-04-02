//
//		File Name ： WinCamera.cpp
//		Production： 2023/6/09
//		Author　　： 石田 恭一	
// 
//		ゲームカメラの実装を行ったクラス
//
//////////////////////////////////////////////////////////////////////////
//						Cameraのクラス									// 
//////////////////////////////////////////////////////////////////////////
#include "pch.h"
#include "WinCamera.h"

//	カメラの位置への距離に対する割合
const float WinCamera::EYE_RATE = 0.03f;
//	注視点への距離に対する割合
const float WinCamera::TARGET_RATE = 0.1f;

/// <summary>
/// コンストラクタ
/// </summary>
WinCamera::WinCamera()
{
}

/// <summary>
/// デストラクタ
/// </summary>
WinCamera::~WinCamera()
{
    using namespace DirectX::SimpleMath;

    // ウィンドウサイズを取得する
    RECT size = MyLib::ScreenResources::GetInstance()->GetDeviceResources()->GetOutputSize();

    float Near = 0.1f;
    float Far = 1200.0f;

    // プロジェクションを生成する
    MyLib::ScreenResources::GetInstance()->SetProjectionMatrix
    (
        Matrix::CreatePerspectiveFieldOfView
        (
            DirectX::XMConvertToRadians(45.0f),
            static_cast<float>(size.right) / static_cast<float>(size.bottom),
            Near,
            Far
        )
    );
}

/// <summary>
/// 入れ替わる前に呼び出す
/// </summary>
/// <param name="finiteStateMachine">オーナー</param>
void WinCamera::Enter(Camera::CAMERASTATE* finiteStateMachine)
{
	UNREFERENCED_PARAMETER(finiteStateMachine);

    using namespace DirectX::SimpleMath;

    // ウィンドウサイズを取得する
    RECT size = MyLib::ScreenResources::GetInstance()->GetDeviceResources()->GetOutputSize();

    float Near = 0.1f;
    float Far = 1200.0f;

    // プロジェクションを生成する
    MyLib::ScreenResources::GetInstance()->SetProjectionMatrix
    (
        Matrix::CreatePerspectiveFieldOfView
        (
            DirectX::XMConvertToRadians(100.0f),
            static_cast<float>(size.right) / static_cast<float>(size.bottom),
            Near,
            Far
        )
    );
}

/// <summary>
/// 実行する
/// </summary>
/// <param name="finiteStateMachine">オーナー<</param>
/// <param name="elapsedTime">経過時間</param>
void WinCamera::Execute(Camera::CAMERASTATE* finiteStateMachine, const DX::StepTimer& timer)
{
	UNREFERENCED_PARAMETER(timer);
	//	カメラを取得する
	Camera* camera = finiteStateMachine->GetOwner();
	//	追従ターゲット
	DirectX::SimpleMath::Vector3 target = finiteStateMachine->GetOwner()->GetOrijinalTargetPosition();

    //  カメラをプレイヤーにどアップさせる
	target.z = target.z - 7.0f;
	target.y = target.y - 16.0f;
	target.x = target.x - 0.0f;

	//	ターゲットの追従
	camera->SetTargetPosition(DirectX::SimpleMath::Vector3::Lerp(camera->GetTargetPosition(), target, TARGET_RATE));
	camera->SetEyePosition(DirectX::SimpleMath::Vector3::Lerp(camera->GetEyePosition(),		  target, EYE_RATE));
}

/// <summary>
/// 退出時の処理
/// </summary>
/// <param name="finiteStateMachine">オーナー</param>
void WinCamera::Exit(Camera::CAMERASTATE* finiteStateMachine)
{
	UNREFERENCED_PARAMETER(finiteStateMachine);
}
