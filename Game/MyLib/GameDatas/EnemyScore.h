//
//		File Name ： EnemyScore.h
//		Production： 2024/4/02
//		Author　　： 石田 恭一	
// 
//		JSONファイルを読み込む際の情報取ヘッダー
//
#pragma once

struct EnemyScore
{
	
	/// <summary>
	/// コンストラクタ
	/// </summary>
	EnemyScore()
	{

	}

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyScore() = default;

	//	変数
public:

	//	プレイヤーの体力
	int							 normalScore;
	//	突撃の体力
	int							 tacleScore;
	//	ボスの体力
	int							 bossScore;
};