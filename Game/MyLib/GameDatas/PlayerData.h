//
//		File Name ： PlayerData.h
//		Production： 2024/4/02
//		Author　　： 石田 恭一	
// 
//		JSONファイルを読み込む際の情報取ヘッダー
//
#pragma once

struct PlayerData
{
	
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="health">体力</param>
	/// <param name="position">座標</param>
	/// <param name="modelScale">モデルの大きさ</param>
	/// <param name="turnSpeed">振り向く速度</param>
	/// <param name="winAnimationTime">勝利時のアニメーション</param>
	/// <param name="deathAnimationTime">死亡時のアニメーション</param>
	/// <param name="gravity">重力</param>
	PlayerData(
		const int& health , 
		const DirectX::SimpleMath::Vector3& position, 
		const DirectX::SimpleMath::Vector3& modelScale, 
		const float& turnSpeed,
		const float& winAnimationTime,
		const float& deathAnimationTime,
		const float& gravity
	)
		:
		playerHealth(health),
		position(position),
		modelScale(modelScale),
		winAnimationTime(winAnimationTime),
		deathAnimationTime(deathAnimationTime),
		gravity(gravity)
	{

	}

	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayerData() = default;

	//	変数
public:

	//	プレイヤーの体力
	int							 playerHealth;
	//	プレイヤーの座標
	DirectX::SimpleMath::Vector3 position;
	//	プレイヤーのモデルの大きさ
	DirectX::SimpleMath::Vector3 modelScale;
	//	振り向く速度
	float						 turnSpeed;
	//	勝利時のアニメーション時間
	float						 winAnimationTime;
	//	死亡時のアニメーション時間
	float						 deathAnimationTime;
	//	重力
	float						 gravity;
	
};