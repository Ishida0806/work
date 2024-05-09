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
    m_healthUpEffectRenderTime(0.0f),
	m_swingSpeedEffectRenderTime(0.0f),
	m_speedUpEffectRenderTime(0.0f),
	m_powerUpEffectRenderTime(0.0f),
	m_speedUpEffectIsActive(false),
	m_healthUpEffectIsActive(false),
	m_swingSpeedEffectIsActive(false),
	m_powerUpEffectIsActive(false)
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
	m_effects.push_back(std::make_unique<PlayerPowerEffect>());
	m_effects.push_back(std::make_unique<PlayerSwingSpeedEffect>());

	//  初期化
	for (const auto& effect : m_effects)
		effect->Initialize();
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="timer">タイマー</param>
void PlayPostEffect::Update(const DX::StepTimer& timer)
{
    // 経過時間を更新
    m_elapsedTime += static_cast<float>(timer.GetElapsedSeconds());

    // プレイヤーの状態変化をチェックし、エフェクトをリセット
    ResetEffectsIfPlayerStatusChanged();

    // プレイヤーのHP低下状態をチェックし、タスクに追加
    CheckAndAddPlayerHPCrisisEffect();

    // プレイヤーのステータス上昇処理
    HandlePlayerStatusUpgrade(timer);

    // タスクに登録されたエフェクトを更新
    UpdateRegisteredEffects(timer);

    // タスクをクリア
    m_task.clear();
}

/// <summary>
/// プレイヤーの状態変化をチェックし、エフェクトをリセット
/// </summary>
void PlayPostEffect::ResetEffectsIfPlayerStatusChanged()
{
    if (m_playerHPBar->IsBad() ||
        m_player->ChooseHealthUP() ||
        m_player->ChooseSpeedUP() ||
        m_player->ChoosePowerUP() ||
        m_player->ChooseSwingSpeedUP())
    {
        for (const auto& effect : m_effects)
        {
            // ピンチエフェクトは例外
            if (effect->GetEffectType() == PostEffect::PostEffectType::PlayerHPCrisis) continue;
            effect->ResetColorAndTime();
        }
    }
}

/// <summary>
/// プレイヤーのHP低下状態をチェックし、タスクに追加する
/// </summary>
void PlayPostEffect::CheckAndAddPlayerHPCrisisEffect()
{
    if (m_playerHPBar->IsBad())
    {
        m_task.push_back(PostEffect::PostEffectType::PlayerHPCrisis);
    }
    else
    {
        for (const auto& effect : m_effects)
        {
            // ピンチエフェクト以外は更新しない
            if (effect->GetEffectType() != PostEffect::PostEffectType::PlayerHPCrisis) continue;
            effect->ResetLerpColor();
        }
    }
}

/// <summary>
/// プレイヤーのステータス上昇処理を行う
/// </summary>
/// <param name="timer">タイマー</param>
void PlayPostEffect::HandlePlayerStatusUpgrade(const DX::StepTimer& timer)
{
    HandleStatusUpgrade(timer , m_player->ChooseHealthUP(),      m_healthUpEffectIsActive,   m_healthUpEffectRenderTime,    PostEffect::PostEffectType::HealthUP);
    HandleStatusUpgrade(timer , m_player->ChooseSpeedUP(),       m_speedUpEffectIsActive,    m_speedUpEffectRenderTime,     PostEffect::PostEffectType::SpeedUP);
    HandleStatusUpgrade(timer , m_player->ChooseSwingSpeedUP(),  m_swingSpeedEffectIsActive, m_swingSpeedEffectRenderTime,  PostEffect::PostEffectType::SwingSpeedUP);
    HandleStatusUpgrade(timer , m_player->ChoosePowerUP(),       m_powerUpEffectIsActive,    m_powerUpEffectRenderTime,     PostEffect::PostEffectType::PowerUP);
}

/// <summary>
/// プレイヤーのステータス上昇処理を行う
/// </summary>
/// <param name="timer">タイマー</param>
/// <param name="isEffectActive">エフェクトが有効かどうか</param>
/// <param name="effectRenderTime">エフェクトの描画時間</param>
/// <param name="effectType">エフェクトのタイプ</param>
void PlayPostEffect::HandleStatusUpgrade(const DX::StepTimer& timer, bool isUpgraded, bool& isEffectActive, float& effectRenderTime, PostEffect::PostEffectType effectType)
{
    if (isUpgraded)
    {
        m_player->SelectedUpStatus(effectType);
        isEffectActive = true;
        effectRenderTime = 0.0f;
        m_task.push_back(effectType);
    }

    if (isEffectActive)
    {
        effectRenderTime += static_cast<float>(timer.GetElapsedSeconds());

        //  経過時間を越していたらフラグを折り、早期リターン
        if (effectRenderTime > RENDER_EFFECT_TIME)
        {
            isEffectActive = false;

            return;
        }
        //  ここまで来れたらまだ表示時間
        m_task.push_back(effectType);
    }
}

/// <summary>
/// 登録されたエフェクトを更新する
/// </summary>
/// <param name="timer">タイマー</param>
void PlayPostEffect::UpdateRegisteredEffects(const DX::StepTimer& timer)
{
    if (!m_task.empty())
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
