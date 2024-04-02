//
//		File Name ： PlayInfo.h
//		Production： 2023/10/17
//		Author　　： 石田 恭一
//
//		プレイシーンで起こった情報を記録する
//		
#include "pch.h"
#include "PlayInfo.h"

//	ポインター
std::unique_ptr<PlayInfo> PlayInfo::m_playInfo = nullptr;
//	スコアの最大値
const int PlayInfo::MAX_SCORE = 9999;

/// <summary>
/// プレイインフォを取得する
/// </summary>
/// <returns></returns>
PlayInfo* const PlayInfo::GetInstance()
{
	//	存在していないなら作成
	if (!m_playInfo)
	{
		m_playInfo.reset(new PlayInfo());		
	}

	//	アドレスを返す
	return m_playInfo.get();
}

/// <summary>
/// コンストラクタ
/// </summary>
PlayInfo::PlayInfo()
	:m_level(0),
	m_score(0),
	m_normalEnemyKnockNum(0),
	m_tackleEnemyKnockNum(0),
	m_bossEnemyKnockNum(0),
	m_elapsedTime(0.0f)
{
}


/// <summary>
/// デストラクタ
/// </summary>
PlayInfo::~PlayInfo()
{
}

/// <summary>
/// 初期化を行う
/// </summary>
void PlayInfo::Initialize()
{
	m_level = 0;
	m_score = 0;
	m_normalEnemyKnockNum = 0;
	m_tackleEnemyKnockNum = 0;
	m_bossEnemyKnockNum = 0;
	m_elapsedTime = 0.0f;
}

/// <summary>
/// 通常敵の撃破数をプラスする
/// </summary>
void PlayInfo::KnockNormal()
{
	m_normalEnemyKnockNum++;
}

/// <summary>
/// 突撃敵の撃破数をプラスする
/// </summary>
void PlayInfo::KnockTackle()
{
	m_tackleEnemyKnockNum++;
}

/// <summary>
/// ボス敵の撃破数をプラスする
/// </summary>
void PlayInfo::KnockBoss()
{
	m_bossEnemyKnockNum++;
}

/// <summary>
/// スコアを上げる
/// </summary>
/// <param name="score">何スコア？</param>
void PlayInfo::UpScore(const int& score)
{
	m_score += score;

	//スコアをオーバーしてたら整える
	m_score = Utility::Clamp(m_score, 0, MAX_SCORE);
}

/// <summary>
/// 経過時間を設定する
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void PlayInfo::SetElapsedTime(const float& elapsedTime)
{
	m_elapsedTime = elapsedTime;
}
