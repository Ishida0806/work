//
//		File Name ： PlayerStatus.h
//		Production： 2023/1/30
//		Author　　： 石田 恭一	
//
#pragma once
#include "Game/MyLib/Scenes/PlayScene/Object/PlayerExperiencePoint/PlayerExperiencePoint.h"

class PlayerStatus 
{
	//	アクセサ
public:

	//	プレイヤーの経験値のポインターを取得する
	PlayerExperiencePoint*			 GetPlayerEXPoint()			const { return m_playerEP.get(); }
	//	レベルを取得する
	int								 GetPlayerLevel()			const { return m_level; }
	//	体力の最大値を取得
	int								 GetMaxHealth()				const { return m_maxHealth; }
	//	体力を取得
	int								 GetHealth()				const { return m_health; }
	//	攻撃力を取得
	int								 GetPower()					const { return m_power + m_attckPower; }
	//	素早さを取得する
	float							 GetSpeed()					const { return m_speed; }
	//	力UPを選んだ？
	bool							 ChoosePowerUP()			const { return m_powerUP; }
	//	速度UPを選んだ？
	bool							 ChooseSpeedUP()			const { return m_speedUP; }
	//	体力UPを選んだ？
	bool							 ChooseHealthUP()			const { return m_healthUP; }
	//	ダメージを受けたか？
	bool							 IsDamege()					const { return m_isDamege; }
	//	無敵時間か？
	bool							 IsInvincible()				const { return m_isInvincible; }
	//	体力をゼロにする
	void HealthZero();
	//	無敵状態を設定する
	void SetInvincible(const bool& flag);
	//	ダメージ状態の設定する
	void SetDamegeCondition(const bool& flag);
	//	ダメージを設定する
	void SetDamege(const int& damege);
	//	体力を増やす
	void UpMaxHP();
	//	速度を増やす
	void UpSpeed();
	//	力が上がる
	void UpPower();
	//	レベルが上がった！
	void UpLevel();

	//	定数
public:

	//	プレイヤーの最初のレベル
	static const int						  FIRST_LEVEL;
	//	プレイヤーの力
	static const int						  FIRST_POWER;
	//	歩く速度
	static const float						  FIRST_SPEED;
	//	回復する値
	static const int						  RECOVERY_VALUE;
	//	無敵時間
	static const float						  INVINCIBLE_TIME;
	//	パワーアップタイム
	static const float						  POWER_UP_TIME;
	//	回復時間
	static const float						  RECOVERY_TIME;

	//	変数
private:

	//	プレイヤーの経験値を管理
	std::unique_ptr<PlayerExperiencePoint>			 m_playerEP;
	//	プレイヤー
	Player*											 m_player;
	//	レベル
	int												 m_level;
	//	体力の最大値
	int												 m_maxHealth;
	//	体力
	int												 m_health;
	//	プレイヤーの攻撃力
	int												 m_power;
	//	一時的な攻撃職の上場
	int												 m_attckPower;
	//	無敵時間か？
	float											 m_invincibleTime;
	//	回復が可能になるまでの時間	
	float											 m_lifeRerecoveryTime;
	//	パワーアップ継続時間
	float											 m_powerUPTime;
	//	速度
	float											 m_speed;
	//	回復中か？
	bool											 m_isRecovery;
	//	パワーアップ中
	bool											 m_isPowerUP;
	//	速度が上がった！
	bool											 m_healthUP;
	//	体力がが上がった！
	bool											 m_speedUP;
	//	力がが上がった！
	bool											 m_powerUP;
	//	ダメージを受けた！	
	bool											 m_isDamege;
	//	無敵時間か？
	bool											 m_isInvincible;

	//	関数
public:

	//	コンストラクタ
	PlayerStatus(Player* player, const int& health);
	//	デストラクタ
	~PlayerStatus();
	//	初期化処理
	void Initialize();
	//	更新処理
	void Update(const DX::StepTimer& timer);
	// プレイヤーがパワーアップアイテムを取得した
	void GetPowerUPItem();
	// プレイヤーが回復アイテムを取得した
	void GetRecoveryItem();

	//	埋め込み関数
private:

	//	回復を行う
	void Recovery(const DX::StepTimer& timer);
	//	パワーアップ状態の制限を確認する
	void CheckPowerUP(const DX::StepTimer& timer);
	//	レベルアップしたフラグを元に戻す
	void CheckLevelUP();
	//	無敵かどうか確認する
	void CheckInvincibility(const DX::StepTimer& timer);
};