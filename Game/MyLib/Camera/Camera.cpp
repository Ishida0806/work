//
//		File Name ： Camera.cpp
//		Production： 2023/6/09
//		Author　　： 石田 恭一	
// 
//		ゲームカメラの実装を行ったクラス
//
//////////////////////////////////////////////////////////////////////////
//						Cameraのクラス									// 
//////////////////////////////////////////////////////////////////////////
#include "pch.h"
#include "Camera.h"

#include "Game/MyLib/Scenes/PlayScene/Object/Player.h"
#include "ShakeCamera.h"
#include "DeathCamera.h"
#include "FadeCamera.h"
#include "IdleCamera.h"
#include "WinCamera.h"

//	走った時のオフセット
const DirectX::SimpleMath::Vector3 Camera::DASH_OFFSET_POSITION = DirectX::SimpleMath::Vector3(0.0f, 4.0f, 2.0f);

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="eye">カメラ位置</param>
/// <param name="target">視点座標</param>
/// <param name="up">上方向ベクトル</param>
/// <param name="player">プレイヤー</param>
Camera::Camera(
	const DirectX::SimpleMath::Vector3& eye, 
	const DirectX::SimpleMath::Vector3& target, 
	const DirectX::SimpleMath::Vector3& up, 
	Player* player)
	:m_eye(eye),
	m_target(target),
	m_up(up),
	m_player(player),
	m_isFade(false),
	m_isDeathCamera(false),
	m_isShake(false)
{
}

/// <summary>
/// デストラクタ
/// </summary>
Camera::~Camera()
{

}

/// <summary>
/// 初期化
/// </summary>
void Camera::Initialize()
{
	//	有限ステートマシーンを作成
	m_fsm = std::make_unique<CAMERASTATE>(this);
	//	ステートの追加
	m_fsm->RegisterState(CameraState::Idle,  new IdleCamera());
	m_fsm->RegisterState(CameraState::Shake, new ShakeCamera());
	m_fsm->RegisterState(CameraState::Fade,  new FadeCamera());
	m_fsm->RegisterState(CameraState::Death, new DeathCamera());
	m_fsm->RegisterState(CameraState::Win,	 new WinCamera());
	//	始めるステートを選ぶ
	m_fsm->Start(Camera::CameraState::Fade);
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="timer">タイマー</param>
/// <param name="isFade">フェード中か？</param>
void Camera::Update(const DX::StepTimer& timer, const bool& isFade)
{
	//	ずらす座標
	DirectX::SimpleMath::Vector3 offsetPos = DASH_OFFSET_POSITION;

	///	ダッシュ中なら少し視野を離す
	if (!m_player->IsDash())	offsetPos = DirectX::SimpleMath::Vector3::Zero;

	//	追従ターゲットの更新
	m_originalTarget = m_player->GetPosition() + offsetPos;
	//	ダメージ
	m_isShake		 = m_player->IsDamege();
	//	フェード
	m_isFade		 = isFade;
	//	プレイヤーが死亡したら変える
	if (m_player->IsAlive())		m_fsm->RequestTransition(Camera::CameraState::Death);	
	//	プレイヤーが勝利したら変える
	if (m_player->IsWinAnimation())	m_fsm->RequestTransition(Camera::CameraState::Win);	
	//	有限ステートマシーンの更新
	m_fsm->Update(timer);
}

/// <summary>
/// 追従ターゲットを設定する
/// </summary>
/// <param name="position">座標</param>
void Camera::SetOrijinalTargetPosition(const DirectX::SimpleMath::Vector3& position)
{
	m_originalTarget = position;
}

/// <summary>
/// ターゲット座標を設定する
/// </summary>
/// <param name="position">座標</param>
void Camera::SetTargetPosition(const DirectX::SimpleMath::Vector3& position)
{
	m_target = position;
}

/// <summary>
/// アイを設定する
/// </summary>
/// <param name="position">座標</param>
void Camera::SetEyePosition(const DirectX::SimpleMath::Vector3& position)
{
	m_eye = position;
}

/// <summary>
/// 揺らすモードを戻す
/// </summary>
void Camera::CompletedShake()
{
	m_isShake = false;
}

/// <summary>
/// デスカメラを取得
/// </summary>
void Camera::InDeathCamera()
{
	m_isDeathCamera = true;
}