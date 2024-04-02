
//
//		File Name ： Player2D.h
//		Production： 2023/11/03
//		Author　　： 石田 恭一	
// 
#pragma once

class Player2D
{
	//	定数
public:

	//	プレイヤー画像の真ん中の座標
	static const DirectX::SimpleMath::Vector2 PLAYER_ORIGIN_TEXTURE;
	//	プレイヤーのデフォルトの大きさ
	static const float						  PLAYER_BASE_SCALE;
	//	動く速さ
	static const float						  MOVE_PLAYER_SPEED;

	//	列挙型
public:

	//	プレイヤーアニメーションの状態
	enum class PLAYER_STATE
	{
		IDLE = 0,
		FIRST = 1,
		SECOND = 2,

		OverID
	};

	//		アクセサ
public:


	inline PLAYER_STATE GetState()				const { return m_playerState; }
	inline float		GetFinAnimationTime()	const { return m_playerAnimationTime; }

	//	変数
private:

	//	プレイヤーの画像
	ID3D11ShaderResourceView*		m_texture;
	//	プレイヤーの座標
	DirectX::SimpleMath::Vector2	m_position;
	//	プレイヤーのアニメーション状態
	PLAYER_STATE					m_playerState;
	//	プレイヤーの大きさを初期化する
	DirectX::SimpleMath::Vector2	m_scale;
	//	プレイヤーのアニメーションの時間
	float							m_playerAnimationTime;



public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="texture">画像</param>
	/// <param name="position">座標</param>
	Player2D(ID3D11ShaderResourceView* texture, const DirectX::SimpleMath::Vector2 position);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Player2D();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="timer">タイマー</param>
	void Update(const DX::StepTimer& timer);

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

	/// <summary>
	/// プレイヤーのアニメーションを開始する
	/// </summary>
	void BeginChangeSceneAnimation();

private:

	void UpdatePlayerState(const DX::StepTimer& timer);

};