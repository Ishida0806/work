
//
//		File Name ： PushSeal.h
//		Production： 2023/11/11
//		Author　　： 石田 恭一
//
#pragma once

class PushSeal
{
	//	アクセサ
public:

	inline bool IsTop() const { return m_isTop; }

	//	定数
public:

	//	共通の誤差範囲
	static const float						   ERROR_RANGE;
	//	共通の速度
	static const float						   SEAL_SPEED;
	//	ターゲットのY座標
	static const DirectX::SimpleMath::Vector2  MOVE_TARGET_POSITION;
	//	目標の判子を押す座標
	static const DirectX::SimpleMath::Vector2  TARGET_PUSH_POSITION;
	//	目標の画面外の座標
	static const DirectX::SimpleMath::Vector2  TARGET_FAR_POSITION;

	//	列挙型
private:

	//	スタンプの挙動
	enum class PUSHSEAL_STATE
	{
		MoveTarget,
		Push,
		MoveOut,
		Finish,

		OverID
	};


	//	変数
private:

	//	画像
	ID3D11ShaderResourceView*		 m_texture;
	//	座標
	DirectX::SimpleMath::Vector2	 m_position;
	//	真ん中の座標
	DirectX::SimpleMath::Vector2	 m_originPosition;
	//	大きさ
	DirectX::SimpleMath::Vector2	 m_scale;
	//	角度
	float							 m_angle;
	//	上側を行っているか？
	bool							 m_isTop;
	//	上側にいったか？
	bool							 m_moveTop;
	//	下側にいったか？
	bool							 m_moveDown;
	//	スタンプをおす挙動
	PUSHSEAL_STATE					 m_stateSeal;


	//	関数
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="texture">画像</param>
	/// <param name="position">座標</param>
	/// <param name="originPosition">真ん中の座標</param>
	PushSeal(
		const DirectX::SimpleMath::Vector2& position,
		const DirectX::SimpleMath::Vector2& originPosition
	);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~PushSeal();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

	//	埋め込み関数
private:

	/// <summary>
	/// ターゲットの場所に移動を行う
	/// </summary>
	void MoveTarget();

	/// <summary>
	/// スタンプを押す
	/// </summary>
	void Push();

	/// <summary>
	/// 外へ向かう
	/// </summary>
	void MoveOut();

};