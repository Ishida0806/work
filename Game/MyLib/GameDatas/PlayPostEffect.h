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
#include "PlayerSwingSpeedEffect.h"

class PlayerHPBar;
class Player;

class PlayPostEffect
{
    // 定数
public:
    
    // エフェクト描画時間
    static const float RENDER_EFFECT_TIME; 

    // 関数
public:

    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="playerHPBar">プレイヤーHpBar</param>
    /// <param name="player">プレイヤー</param>
    PlayPostEffect(PlayerHPBar* playerHPBar, Player* player);

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~PlayPostEffect();

    /// <summary>
    /// 初期化処理
    /// </summary>
    void Initialize();

    /// <summary>
    /// 更新処理
    /// </summary>
    /// <param name="timer">タイマー</param>
    void Update(const DX::StepTimer& timer);

    /// <summary>
    /// 描画処理
    /// </summary>
    void Draw(); 

    // 変数
private:
    
    // プレイヤーのHPBar
    PlayerHPBar* m_playerHPBar;
    // プレイヤー
    Player* m_player;
    // 実行するタスク
    std::vector<PostEffect::PostEffectType> m_task; 
    // ポストエフェクト
    std::vector<std::unique_ptr<PostEffect>> m_effects; 
    // 体力UP時のエフェクト描画時間
    float m_healthUpEffectRenderTime;
     // 速度UP時のエフェクト描画時間
    float m_speedUpEffectRenderTime;
    // 振る速度UP時のエフェクト描画時間
    float m_swingSpeedEffectRenderTime; 
    // 力UP時のエフェクト描画時間
    float m_powerUpEffectRenderTime; 
    // 速度UPエフェクトが有効か
    bool m_speedUpEffectIsActive;
    // 体力UPエフェクトが有効か
    bool m_healthUpEffectIsActive; 
    // 力UPエフェクトが有効か
    bool m_powerUpEffectIsActive;
    // 振る速度UPエフェクトが有効か
    bool m_swingSpeedEffectIsActive; 

    //  埋め込みyyy関数
private:

    /// <summary>
    /// プレイヤーのステータス変化に応じて、エフェクトをリセットする
    /// </summary>
    void ResetEffectsIfPlayerStatusChanged();

    /// <summary>
    /// プレイヤーのHP低下状態をチェックし、タスクに追加する
    /// </summary>
    void CheckAndAddPlayerHPCrisisEffect();

    /// <summary>
    /// プレイヤーのステータス上昇処理を行う
    /// </summary>
    /// <param name="timer">タイマー</param>
    void HandlePlayerStatusUpgrade(const DX::StepTimer& timer);

    /// <summary>
    /// プレイヤーのステータス上昇処理を行う
    /// </summary>
    /// <param name="timer">タイマー</param>
    /// <param name="isEffectActive">エフェクトが有効かどうか</param>
    /// <param name="effectRenderTime">エフェクトの描画時間</param>
    /// <param name="effectType">エフェクトのタイプ</param>
    void HandleStatusUpgrade(const DX::StepTimer& timer , bool isUpgraded, bool& isEffectActive, float& effectRenderTime, PostEffect::PostEffectType effectType);

    /// <summary>
    /// 登録されたエフェクトを更新する
    /// </summary>
    /// <param name="timer">タイマー</param>
    void UpdateRegisteredEffects(const DX::StepTimer& timer);
};