//
//		File Name ： PlaySceneWave.h
//		Production： 2024/1/23
//		Author　　： 石田 恭一	
//
#pragma once
#include "Game/MyLib/GameDatas/Number.h"
#include "Game/MyLib/Scenes/PlayScene/Wave/ButtleWave.h"

class PlayScene;

class PlaySceneWave
{
	//	定数
public:

	//	ウェーブの色情報
	static const DirectX::SimpleMath::Color WAVE_COLOR;

	//	アクセサ
public:

	//	現在のウェーブ数を取得する
	inline int GetCurrentWave()						const		{ return m_currentWave; }
	//	最大ウェーブ数を取得する
	inline int GetMaxWave()							const		{ return m_maxWave; }
	//	最終ウェーブか？
	inline bool IsFinalWave()						const		{ return m_isFinalWave; }
	//	敵のデータを取得する
	inline std::vector<EnemyData> GetEnemyData()	const		{ return m_enemyDatas; }

	//	変数
private:

	//	プレイシーン
	PlayScene*										 m_playScene;
	//	スコアの画像
	ID3D11ShaderResourceView*						 m_waveDisplayTexture;
	//	敵のデータ	
	std::vector<EnemyData>							 m_enemyDatas;
	//	最大ステージの数字
	std::unique_ptr<Number>							 m_maxNumber;
	//	現在ステージの数字
	std::unique_ptr<Number>							 m_currentNumber;
	//	最終ウェーブか
	bool											 m_isFinalWave;
	//	現在のウェーブ
	int												 m_currentWave;
	//	最大ウェーブ数
	int												 m_maxWave;


	//	関数
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="playScene">プレイシーン</param>
	PlaySceneWave(PlayScene* playScene);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlaySceneWave();

	/// <summary>
	///	初期化する
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画する
	/// </summary>
	void Draw();

	/// <summary>
	/// 次のウェーブへ行く
	/// </summary>
	void NextWave();

	/// <summary>
	/// スポーンした敵オブジェクトのデータを削除する
	/// </summary>
	void DeleteSpawnedEnemyData();
};

