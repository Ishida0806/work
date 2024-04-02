//
//		File Name ： PlayerExperiencePoint.h
//		Production： 2023/11/30
//		Author　　： 石田 恭一	
//	
#pragma once

class Player;

class PlayerExperiencePoint final
{
	//	アクセサ
public:

	//	必要な経験値を取得する
	inline int GetExperiencePoint()		const { return m_experiencePoint; }
	//	次に必要な経験値を取得する
	inline int GetNeedExperiencePoint() const { return m_needExperiencePoint; }

	//	経験値を取得した
	void SetExperiencePoint(const int& exPoint);

	//	定数
public:

	//	プレイヤーの最大レベル
	static const int MAX_PLAYER_LEVEL;
	//	最初の経験値
	static const int FIRST_LEVEL_EXP;
	//	経験値の増加量
	static const int INCREASE_EXP;

	//	変数
private:
	//	プレイヤー
	Player* m_player;
	//	経験値
	int m_experiencePoint;
	//	次のレベルアップに必要な経験値
	int m_needExperiencePoint;
	//	余剰の経験値
	int m_surplusExperiencePoint;

	//	関数
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="player">プレイヤー<</param>
	PlayerExperiencePoint(Player* player);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayerExperiencePoint();

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="timer">タイマー</param>
	void Update(const DX::StepTimer& timer);

	//	埋め込み関数
private:

	//	経験値を補正する
	void ClampEXP();
};