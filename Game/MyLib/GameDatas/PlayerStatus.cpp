//
//		File Name ： PlayerStatus.cpp
//		Production： 2023/1/30
//		Author　　： 石田 恭一	
// 
//		プレイヤーのステータスの管理クラス
//	
#include "pch.h"
#include "PlayerStatus.h"

//	プレイヤーの最初のレベル
const int PlayerStatus::FIRST_LEVEL		  = 1;
//	プレイヤーの力
const int PlayerStatus::FIRST_POWER		  = 1;
//	回復の値
const int PlayerStatus::RECOVERY_VALUE	  = 10;
//	無敵時間
const float PlayerStatus::INVINCIBLE_TIME = 0.9f;
//	速度
const float PlayerStatus::FIRST_SPEED	  = 0.08f;
//	回復が可能時間
const float PlayerStatus::RECOVERY_TIME	  = 5.5f;
//	パワーアップタイム
const float PlayerStatus::POWER_UP_TIME	  = 15.0f;

/// <summary>
///  コンストラクタ
/// </summary>
/// <param name="player">プレイヤー</param>
/// <param name="health">体力</param>
PlayerStatus::PlayerStatus(Player* player, const int& health)
	:m_player(player),
	m_health(health),
	m_maxHealth(health),
	m_power(FIRST_POWER),
	m_level(FIRST_LEVEL),
	m_attckPower(0),
	m_powerUPTime(0.0f),
	m_speed(0.0f),
	m_invincibleTime(0.0f),
	m_lifeRerecoveryTime(0.0f),
	m_healthUP(false),
	m_speedUP(false),
	m_isPowerUP(false),
	m_isDamege(false),
	m_powerUP(false),
	m_isRecovery(false),
	m_isInvincible(false)
{

}

/// <summary>
/// デストラクタ
/// </summary>
PlayerStatus::~PlayerStatus()
{
}

/// <summary>
/// 初期化処理
/// </summary>
void PlayerStatus::Initialize()
{
	//	速度を決める
	m_speed = FIRST_SPEED;
	//	プレイヤーの経験値を作成する
	m_playerEP = std::make_unique<PlayerExperiencePoint>(m_player);
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="timer">タイマー</param>
void PlayerStatus::Update(const DX::StepTimer& timer)
{
	//	経験値状態を確認する
	m_playerEP->Update(timer);
	// レベルアップしたフラグを元に戻す
	CheckLevelUP();
	// 時間経過で体力の回復を行う
	Recovery(timer);
	//	無敵になっていたら時間経過で戻す
	CheckInvincibility(timer);
	//	パワーアップ状態の制限を確認する
	CheckPowerUP(timer);
}

/// <summary>
/// プレイヤーがアイテムを取得した
/// </summary>
void PlayerStatus::GetPowerUPItem()
{
	m_powerUPTime = 0.0f;
	m_isPowerUP = true;
}

/// <summary>
/// プレイヤーが回復アイテムを取得した
/// </summary>
void PlayerStatus::GetRecoveryItem()
{
	//	回復する
	m_health += RECOVERY_VALUE * 2;
	//	最大値を超えないように
	m_health = Utility::Clamp(m_health, 0, m_maxHealth);
	//	回復時間はリセットする
	m_lifeRerecoveryTime = 0.0f;
}


/// <summary>
/// レベルアップしたフラグを元に戻す
/// </summary>
void PlayerStatus::CheckLevelUP()
{
	if (m_powerUP)
	{
		m_powerUP = false;
	}
	if (m_speedUP)
	{
		m_speedUP = false;
	}
	if (m_healthUP)
	{
		m_healthUP = false;
	}
}

/// <summary>
/// パワーアップ状態の制限を確認する
/// </summary>
void PlayerStatus::CheckPowerUP(const DX::StepTimer& timer)
{
	if (m_isPowerUP)
	{
		//	攻撃力が1増える
		m_attckPower = FIRST_POWER;
		//	経過時間を足す
		m_powerUPTime += static_cast<float>(timer.GetElapsedSeconds());

		if (m_powerUPTime >= POWER_UP_TIME)
		{
			m_isPowerUP = false;
		}
	}
	else
	{
		m_attckPower = 0;
	}
}

/// <summary>
/// 無敵かどうかを確認する
/// </summary>
/// <param name="timer">タイマー</param>
void PlayerStatus::CheckInvincibility(const DX::StepTimer& timer)
{
	//	時間経過で無敵状態を治す
	if (!m_isInvincible)	return;

	//	無敵時間を取得する
	m_invincibleTime += static_cast<float>(timer.GetElapsedSeconds());

	//	無敵時間中なら帰れ	
	if (m_invincibleTime >= INVINCIBLE_TIME)	return;

	m_isInvincible = false;
	m_invincibleTime = 0.0f;
}

/// <summary>
/// 時間経過で体力の回復を行う
/// </summary>
/// <param name="timer">タイマー</param>
void PlayerStatus::Recovery(const DX::StepTimer& timer)
{
	// もし最大健康値以上であれば、回復処理を行わない
	if (m_maxHealth <= m_health)
		return;

	// 回復時間 に経過時間を加算
	m_lifeRerecoveryTime += static_cast<float>(timer.GetElapsedSeconds());

	// 経過時間以上経過した場合、回復処理を実行
	if (m_lifeRerecoveryTime >= RECOVERY_TIME)
	{
		// 経過時間をリセット
		m_lifeRerecoveryTime = 0.0f;

		// もし体力を回復させても最大健康値を超えない場合
		if (m_health + RECOVERY_VALUE <= m_maxHealth)
		{
			// 体力値を回復させる
			m_health += RECOVERY_VALUE;
		}
		else
		{
			// 最大体力値に設定
			m_health = m_maxHealth;
		}
		//	指定されたSEを流す
		AudioManager::GetInstance()->PlaySoundEffectSE(L"RecoverSE01");
	}
}

/// <summary>
/// 体力をゼロにする
/// </summary>
void PlayerStatus::HealthZero()
{
	m_health = 0;
}

/// <summary>
/// 無敵にする
/// </summary>
/// <param name="flag">フラグ</param>
void PlayerStatus::SetInvincible(const bool& flag)
{
	m_isInvincible = flag;
}

/// <summary>
/// ダメージ状態を設定する
/// </summary>
/// <param name="flag"></param>
void PlayerStatus::SetDamegeCondition(const bool& flag)
{
	m_isDamege = flag;
}

/// <summary>
///	ダメージを設定する
/// </summary>
/// <param name="damege">ダメージ</param>
void PlayerStatus::SetDamege(const int& damege)
{
	m_health -= damege;
	//	ダメージが0以上なら状態をつける
	if (damege != 0)
	{
		m_lifeRerecoveryTime = 0.0f;
		m_isInvincible = true;
		m_isDamege = true;
	}
}

/// <summary>
/// 体力の最大値を増やす
/// </summary>
/// <param name="value">増加量</param>
void PlayerStatus::UpMaxHP()
{
	m_maxHealth += 20;
	//	体力が選ばれた
	m_healthUP = true;
}

/// <summary>
/// 速度を増やす
/// </summary
void PlayerStatus::UpSpeed()
{
	m_speed += 0.01f;
	//	速度が選ばれた
	m_speedUP = true;
}

/// <summary>
/// 力が上がる
/// </summary>
void PlayerStatus::UpPower()
{
	m_power++;
	//	パワーが選ばれた
	m_powerUP = true;
}

/// <summary>
///	レベルが上がった
/// </summary>
void PlayerStatus::UpLevel()
{
	m_level++;
}