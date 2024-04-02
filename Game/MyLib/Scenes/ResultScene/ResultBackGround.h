//
//		File Name ： ResultBackGround.h
//		Production： 2023/11/12
//		Author　　： 石田 恭一	
//
#pragma once

class ResultBackGround
{
	//	定数
public:

	//	背景画像の座標
	static const DirectX::SimpleMath::Vector2 BACKGROUND_POSITION;
	//	背景画像の真ん中の座標
	static const DirectX::SimpleMath::Vector2 BACKGROUND_ORIGIN_POSITION;
	//	大きくなる速度
	static const float						  SCLAE_UP_SPEED;
	//	規定値を超えた後の大きくなる速度
	static const float						  SCLAE_AFTER_SPEED;
	//	目標の大きさ
	static const float						  TARGET_SCALE;
	//	回る速度
	static const float						  TURN_SPEED;
	//	座標の移動速度
	static const float						  POSITION_SPEED;
	//	大きさの誤差範囲
	static const float						  ERROR_RANGE_SCALE;
	//	目標の角度
	static const float						  TARGET_ANGLE;
	//	目標の最終大きさ
	static const float						  TARGET_FINAL_SCALE;


	//	変数
private:

	//	大きさ
	DirectX::SimpleMath::Vector2	m_sacle;
	//	座標
	DirectX::SimpleMath::Vector2	m_position;
	//	画像
	ID3D11ShaderResourceView*		m_texture;
	//	角度
	float							m_targetAngle;
	float							m_angle;

	//	関数
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ResultBackGround();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ResultBackGround();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <returns></returns>
	bool Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

	//	組み込み関数
private:

	/// <summary>
	/// 目標角度までの距離を算出する
	/// </summary>
	/// <param name="targetAngle">目標角度</param>
	/// <returns>目標角度</returns>
	float ConvartTargetAngle(const float& targetAngle);
};