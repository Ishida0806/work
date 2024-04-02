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
	PlayerData()
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