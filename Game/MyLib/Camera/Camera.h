//
//		File Name ： Camera.h
//		Production： 2023/9/07
//		Author　　： 石田 恭一	
//
#pragma once
#include "Game/MyLib/GameDatas/FiniteStateMachine.h"

class Player;

class Camera
{
	//	定数
public:

	//	走った時のオフセット
	static const DirectX::SimpleMath::Vector3 DASH_OFFSET_POSITION;

	//	列挙型
public:

	//	カメラのステート
	enum class CameraState
	{
		Idle  = 0,
		Shake = 1,
		Fade  = 2,
		Death = 3,
		Win	  = 4,

		OverID
	};

	//	エイリアス宣言
public:

	using CAMERASTATE  = FiniteStateMachine<Camera, Camera::CameraState>;
	using ICAMERASTATE = CAMERASTATE::IState;

	// アクセサ
public:

	inline  CAMERASTATE*				GetFSM()					 const { return m_fsm.get(); }
	// カメラの位置を取得
	inline DirectX::SimpleMath::Vector3 GetEyePosition()			 const { return m_eye; }
	// カメラの注視点を取得
	inline DirectX::SimpleMath::Vector3 GetTargetPosition()			 const { return m_target; }

	inline DirectX::SimpleMath::Vector3 GetOrijinalTargetPosition()  const { return m_originalTarget; }
	//	揺れているか
	inline bool							IsShake()					 const { return m_isShake; }
	//	フェード中か
	inline bool							IsFade()					 const { return m_isFade; }
	//	デスカメラ中か
	inline bool							IsDeathCamera()				 const { return m_isDeathCamera; }

	//	ターゲットを設定する
	void SetOrijinalTargetPosition(const DirectX::SimpleMath::Vector3& position);
	//	追従ターゲットを設定する
	void SetTargetPosition(const DirectX::SimpleMath::Vector3& position);
	//	アイを設定する
	void SetEyePosition(const DirectX::SimpleMath::Vector3& position);
	//	揺らすモードを戻す
	void CompletedShake();
	//	デスカメラを取得
	void InDeathCamera();

	//	変数
private:

	//	有限ステートマシーン
	std::unique_ptr<CAMERASTATE> m_fsm;
	// ターゲット
	DirectX::SimpleMath::Vector3 m_originalTarget;
	// 視点
	DirectX::SimpleMath::Vector3 m_eye;
	// 注視点
	DirectX::SimpleMath::Vector3 m_target;
	// 上方向
	DirectX::SimpleMath::Vector3 m_up;
	//	プレイヤー
	Player*						 m_player;
	//	シェイク中か
	bool						 m_isShake;
	//	デスカメラ中か
	bool						 m_isDeathCamera;
	//	フェード中か
	bool						 m_isFade;

	//	関数
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="eye">カメラ位置</param>
	/// <param name="target">視点座標</param>
	/// <param name="up">上方向ベクトル</param>
	/// <param name="player">プレイヤー</param>
	Camera
	(
		const DirectX::SimpleMath::Vector3& eye,
		const DirectX::SimpleMath::Vector3& target,
	    const DirectX::SimpleMath::Vector3& up,
		Player*								player
	);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Camera();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize();
	
	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="timer">タイマー</param>
	/// <param name="isFade">フェード中か？</param>
	void Update(const DX::StepTimer& timer, const bool& isFade);
};