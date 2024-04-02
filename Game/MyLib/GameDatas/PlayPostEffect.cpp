//
//		File Name ： PlayPostEffect.cpp
//		Production： 2023/1/10
//		Author　　： 石田 恭一	
// 
//		画面効果をまとめたクラス
//
#include "pch.h"
#include "PlayPostEffect.h"

#include "Game/MyLib/Scenes/PlayScene/UI/PlayerHPBar.h"
#include "Game/MyLib/Scenes/PlayScene/Object/Player.h"

//	描画時間
const float PlayPostEffect::RENDER_EFFECT_TIME = 0.82f;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="playerHPBar">体力バー</param>
/// <param name="player">プレイヤー</param>
PlayPostEffect::PlayPostEffect(PlayerHPBar* playerHPBar, Player* player)
	:m_playerHPBar(playerHPBar),
	m_player(player),
	m_elapsedTime(0.0f),
	m_powerUPEffectRenderTime(0.0f),
	m_speedUPEffectRenderTime(0.0f),
	m_healthUPEffectRenderTime(0.0f),
	m_speedUPEffectRenderFlag(false),
	m_healthUPEffectRenderFlag(false),
	m_powerUPEffectRenderFlag(false)
{
}

/// <summary>
/// デストラクタ
/// </summary>
PlayPostEffect::~PlayPostEffect()
{
}


/// <summary>
///	初期化処理
/// </summary>
void PlayPostEffect::Initialize()
{
	m_effects.push_back(std::make_unique<PlayerHPCrisisEffect>());
	m_effects.push_back(std::make_unique<PlayerCureEffect>());
	m_effects.push_back(std::make_unique<PlayerSpeedEffect>());
	m_effects.push_back(std::make_unique<PlayerPowerffect>());

	//
	for (const auto& effect : m_effects)
		effect->Initialize();
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="timer">タイマー</param>
void PlayPostEffect::Update(const DX::StepTimer& timer)
{
	//	経過時間を足す
	m_elapsedTime += static_cast<float>(timer.GetElapsedSeconds());

	//	条件を確認したら前の奴は消す
	if (m_playerHPBar->IsBad() ||
		m_player->ChooseHealthUP() ||
		m_player->ChooseSpeedUP() ||
		m_player->ChoosePowerUP()
		)
	{
		for (const auto& effect : m_effects)
		{
			//	ピンチエフェクトは例外
			if (effect->GetEffectType() == PostEffect::PostEffectType::PlayerHPCrisis) continue;

			effect->ResetColorAndTime();
		}
	}

	//	条件を満たしたらタスクに入れる
	if (m_playerHPBar->IsBad())
	{
		m_task.push_back(PostEffect::PostEffectType::PlayerHPCrisis);
	}
	else
	{	
		for (const auto& effect : m_effects)
		{
			//	ピンチエフェクト以外は帰れ
			if (effect->GetEffectType() != PostEffect::PostEffectType::PlayerHPCrisis) continue;
			//	BAD状態ではないので色をだんだん薄くする
			effect->ResetLerpColor();
		}
	}

	if (m_player->ChooseHealthUP())
	{
		m_healthUPEffectRenderFlag = true;
		m_healthUPEffectRenderTime = 0.0f;
	}
	if (m_player->ChooseSpeedUP())
	{
		m_speedUPEffectRenderFlag = true;
		m_speedUPEffectRenderTime = 0.0f;
	}
	if (m_player->ChoosePowerUP())
	{
		m_powerUPEffectRenderFlag = true;
		m_powerUPEffectRenderTime = 0.0f;
	}

	//	体力が上がる条件を満たしたか
	if (m_healthUPEffectRenderFlag)
	{
		m_task.push_back(PostEffect::PostEffectType::HealthUP);

		m_healthUPEffectRenderTime += static_cast<float>(timer.GetElapsedSeconds());

		if (m_healthUPEffectRenderTime > RENDER_EFFECT_TIME)
		{
			m_healthUPEffectRenderFlag = false;
		}
	}
	//	速度が上がる条件を満たしたか
	if (m_speedUPEffectRenderFlag)
	{
		m_task.push_back(PostEffect::PostEffectType::SpeedUP);

		m_speedUPEffectRenderTime += static_cast<float>(timer.GetElapsedSeconds());

		if (m_speedUPEffectRenderTime > RENDER_EFFECT_TIME)
		{
			m_speedUPEffectRenderFlag = false;
		}
	}
	//	力が上がる条件を満たしたか
	if (m_powerUPEffectRenderFlag)
	{
		m_task.push_back(PostEffect::PostEffectType::PowerUP);

		m_powerUPEffectRenderTime += static_cast<float>(timer.GetElapsedSeconds());

		if (m_powerUPEffectRenderTime > RENDER_EFFECT_TIME)
		{
			m_powerUPEffectRenderFlag = false;
		}
	}

	if (m_task.size() != 0)
	{
		for (const auto& task : m_task)
		{
			for (const auto& effect : m_effects)
			{
				if (task != effect->GetEffectType()) continue;
				
				effect->Update(timer);
				
			}
		}
	}		
	//	クリアを行う
	m_task.clear();
}

/// <summary>
/// 描画のタイプ
/// </summary>
void PlayPostEffect::Draw()
{
	//	エフェクトの描画
	for (const auto& effect : m_effects)
	{
		effect->Draw();
	}
}
