
#pragma once

class LevelCardBackGround
{
	//	定数
public:

	//	背景画像の中心点
	static const DirectX::SimpleMath::Vector2 BACKGROUND_ORIGIN_POSITION;
	//	背景画像の初期化Y座標
	static const float						  BACKGROUND_RESTART_POSITION_Y;
	//	入場の速さ
	static const float						  IN_SPEED;
	//	退場の速さ
	static const float						  EXIT_SPEED;
	//	上に上がる速さ
	static const float						  EXIT_SPEED_POSITION_Y;


	//	変数
private:

	//	背景画像の座標
	DirectX::SimpleMath::Vector2				  m_backGroundPosition;
	//	背景画像の目標座標
	DirectX::SimpleMath::Vector2				  m_backGroundTargetPosition;
	//	背景画像の大きさ
	DirectX::SimpleMath::Vector2				  m_backGroundScale;
	//	背景画像
	ID3D11ShaderResourceView*					  m_backGroundTexture;
	//	クリックされた
	bool										  m_isClick;

	//	関数
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="player">プレイヤー</param>
	LevelCardBackGround();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~LevelCardBackGround();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 退出処理
	/// </summary>
	void Exit();

	/// <summary>
	/// 描画する
	/// </summary>
	void Draw();

	//	埋め込み関数
private:

	//	座標の初期化
	void ResetPosition();
};