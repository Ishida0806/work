//
//		File Name ： PlayPostEffect.h
//		Production： 2023/1/10
//		Author　　： 石田 恭一	
//
#pragma once
#include "PostEffect.h"
#include "PlayerHPCrisisEffect.h"
#include "PlayerSpeedEffect.h"
#include "PlayerCureEffect.h"
#include "PlayerPowerffect.h"

class PlayerHPBar;
class Player;

class PlayPostEffect
{
	//	定数
public:

	//	描画時間
	static const float RENDER_EFFECT_TIME;

	//	変数
private:

	//	HPBar
	PlayerHPBar*							  m_playerHPBar;
	//	レベルカード
	Player*									  m_player;
	//	タスク
	std::vector<PostEffect::PostEffectType>	  m_task;
	//	エフェクト
	std::vector<std::unique_ptr<PostEffect>>  m_effects;
	//	経過時間
	float									  m_elapsedTime;
	//	体力UPの描画時間
	float									  m_healthUPEffectRenderTime;
	//	速度UPの描画時間
	float									  m_speedUPEffectRenderTime;
	//	力UPの描画時間
	float									  m_powerUPEffectRenderTime;
	//	速度が上がった際の描画フラグ
	bool									  m_speedUPEffectRenderFlag;
	//	体力が上がった際の描画フラグ
	bool									  m_healthUPEffectRenderFlag;
	//	力が上がった際の描画フラグ
	bool									  m_powerUPEffectRenderFlag;

	//	関数
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	PlayPostEffect(PlayerHPBar* playerHPBar, Player* player);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayPostEffect();

	/// <summary>
	///	初期化処理
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="timer">タイマー</param>
	void Update(const DX::StepTimer& timer);

	/// <summary>
	/// 描画のタイプ
	/// </summary>
	void Draw();
};