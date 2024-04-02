//
//		File Name ： PlayerExperiencePoint.cpp
//		Production： 2023/11/30
//		Author　　： 石田 恭一	
// 
//		経験値を管理取得する
//	
#include "pch.h"
#include "PlayerExperiencePoint.h"

#include "../Player.h"


//	プレイヤーの最大レベル
const int PlayerExperiencePoint::MAX_PLAYER_LEVEL = 10;
//	最初の経験値
const int PlayerExperiencePoint::FIRST_LEVEL_EXP  = 5;
//	経験値の増加量
const int PlayerExperiencePoint::INCREASE_EXP	  = 12;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="player">プレイヤー</param>
PlayerExperiencePoint::PlayerExperiencePoint(Player* player)
	:m_player(player),
	m_experiencePoint(0),
	m_needExperiencePoint(0),
	m_surplusExperiencePoint(0)
{
	m_needExperiencePoint = FIRST_LEVEL_EXP;
}

/// <summary>
/// デストラクタ
/// </summary>
PlayerExperiencePoint::~PlayerExperiencePoint()
{
}

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="timer">タイマー</param>
void PlayerExperiencePoint::Update(const DX::StepTimer& timer)
{
	UNREFERENCED_PARAMETER(timer);

	//	必要経験値値を超えていたら補正する
	ClampEXP();

	//	レベルを取得する
	int level = m_player->GetPlayerLevel();

	//	最大レベルに達したら帰れ
	if (level >= MAX_PLAYER_LEVEL)	 return;


#ifdef _DEBUG
	m_experiencePoint++; 
#endif // _DEBUG



	//	レベルアップに必要な経験値に行っているか確認する
	if (m_experiencePoint >= m_needExperiencePoint)
	{
		//	SEを再生する
		AudioManager::GetInstance()->PlaySoundEffectSE(L"levelUP");
		//	プレイやーのレベルが上がった
		m_player->UpLevel();
		//	現在の経験値はリセットする
		m_experiencePoint	   = 0;
		//	次の目標値を設定する
		m_needExperiencePoint += INCREASE_EXP;
	}

	//	余剰分があったら渡す
	if (m_surplusExperiencePoint > 0)
	{
		m_experiencePoint += m_surplusExperiencePoint;
		m_surplusExperiencePoint = 0;
	}
}

/// <summary>
/// 経験値を補正する
/// </summary>
void PlayerExperiencePoint::ClampEXP()
{
	//	必要経験値値を超えていたら補正する
	if (m_experiencePoint > m_needExperiencePoint)
	{
		//	経験値を超えていたら余剰分をいただく
		m_surplusExperiencePoint += m_experiencePoint - m_needExperiencePoint;
		//	いただいたら超えないように補正する
		m_experiencePoint = m_needExperiencePoint;
	}
}

/// <summary>
/// 経験値を取得した
/// </summary>
/// <param name="exPoint">取得した経験値を</param>
void PlayerExperiencePoint::SetExperiencePoint(const int& exPoint)
{
	m_experiencePoint += exPoint;

	ClampEXP();
}
