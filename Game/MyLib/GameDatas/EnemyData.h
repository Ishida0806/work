//
//		File Name ： EnemyData.h
//		Production： 2024/1/23
//		Author　　： 石田 恭一	
// 
//		JSONファイルを読み込む際の情報取ヘッダー
//
#pragma once

struct EnemyData
{
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="position">座標</param>
	/// <param name="enemyType">識別子</param>
	/// <param name="power">力</param>
	/// <param name="health">体力</param>
	/// <param name="spawnWave">スポーンするウェーブ数</param>
	EnemyData(const DirectX::SimpleMath::Vector3& position, const int& enemyType, const int& health, const int& power, const int& spawnWave)
		:
		position(position),
		enemyType(enemyType),
		health(health),
		power(power),
		spawnWave(spawnWave)
	{

	}

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyData() = default;

	//	変数
public:

	//	敵のタイプ
	int							 enemyType;
	//	スポーンウェーブ
	int							 spawnWave;
	//	体力
	int							 health;
	//	力
	int							 power;
	//	座標
	DirectX::SimpleMath::Vector3 position;
};