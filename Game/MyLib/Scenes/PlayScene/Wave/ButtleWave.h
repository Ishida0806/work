//
//		File Name ： ButtleWave.h
//		Production： 2024/1/23
//		Author　　： 石田 恭一	
//
#pragma once
#include "Game/MyLib/GameDatas/EnemyData.h"

class PlayScene;

class ButtleWave
{
	//	アクセサ
public:

	//	最大ウェーブ数を取得する
	inline int GetMaxWave() const { return m_maxWave; }

	//	変数
private:

	//	プレイシーン
	PlayScene*									m_playScene;
	//	最大ウェーブ
	int											m_maxWave;

	//	関数
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="playScene">プレイシーン</param>
	ButtleWave(PlayScene* playScene);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ButtleWave();

	std::vector<EnemyData> OpenMap();
};