//
//		File Name ： PlayInfo.h
//		Production： 2023/10/17
//		Author　　： 石田 恭一
//
#pragma once

class PlayInfo final
{
	//	定数
public:

	//	スコアの最大値
	static const int MAX_SCORE;

	//	アクセサ
public:

	//	スクリーンのインスタンスを取得する
	static PlayInfo*				const GetInstance();
	//	レベルを取得する
	inline int GetLevel()			const { return m_level;  }
	//	スコアを取得する
	inline int GetScore()			const { return m_score;  }
	//	経過時間を取得する
	inline float GetElapseedTime()	const { return m_elapsedTime;  }
	//	通常の敵の取得する
	inline int GetNormalKnockNum()  const { return m_normalEnemyKnockNum;  }
	//	突撃の敵の数を取得する
	inline int GetTackleKnockNum()  const { return m_tackleEnemyKnockNum;  }
	//	ボスの敵の数を取得する
	inline int GetBossKnockNum()	const { return m_bossEnemyKnockNum;  }

	/// <summary>
	/// スコアを上げる
	/// </summary>
	/// <param name="score">:何スコア？</param>
	void UpScore(const int& score);


	/// <summary>
	/// 経過時間を設定する
	/// </summary>
	/// <param name="elapsedTime">経過時間</param>
	void SetElapsedTime(const float& elapsedTime);

	//	関数
public:
	
	~PlayInfo();

	// 代入は許容しない
	void operator=(const PlayInfo& object) = delete;
	// コピーコンストラクタは許容しない
	PlayInfo(const PlayInfo& object) = delete;

	//	初期化処理
	void Initialize();
	// 通常敵の撃破数をプラスする
	void KnockNormal();
	// 突撃敵の撃破数をプラスする
	void KnockTackle();
	// ボス敵の撃破数をプラスする
	void KnockBoss();

	//	コンストラクタ
private:

	//	コンストラクタ->インスタンスを作成させない
	PlayInfo();

	//	変数
private:

	// スクリーンリソーシーズクラスのインスタンスへのポインタ
	static std::unique_ptr<PlayInfo>		 m_playInfo;
	//	レベル
	unsigned int							 m_level;
	//	通常敵の倒した数
	unsigned int							 m_normalEnemyKnockNum;
	//	突撃敵の倒した数
	unsigned int							 m_tackleEnemyKnockNum;
	//	ボスの倒した数
	unsigned int							 m_bossEnemyKnockNum;
	//	スコア
	int										 m_score;
	//	経過時間
	float									 m_elapsedTime;
};

