//
//		File Name �F PlayPostEffect.h
//		Production�F 2023/1/10
//		Author�@�@�F �Γc ����	
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
    // �萔
public:
    
    // �G�t�F�N�g�`�掞��
    static const float RENDER_EFFECT_TIME; 

    // �֐�
public:

    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="playerHPBar">�v���C���[HpBar</param>
    /// <param name="player">�v���C���[</param>
    PlayPostEffect(PlayerHPBar* playerHPBar, Player* player);

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~PlayPostEffect();

    /// <summary>
    /// ����������
    /// </summary>
    void Initialize();

    /// <summary>
    /// �X�V����
    /// </summary>
    /// <param name="timer">�^�C�}�[</param>
    void Update(const DX::StepTimer& timer);

    /// <summary>
    /// �`�揈��
    /// </summary>
    void Draw(); 

    // �ϐ�
private:
    
    // �v���C���[��HPBar
    PlayerHPBar* m_playerHPBar;
    // �v���C���[
    Player* m_player;
    // ���s����^�X�N
    std::vector<PostEffect::PostEffectType> m_task; 
    // �|�X�g�G�t�F�N�g
    std::vector<std::unique_ptr<PostEffect>> m_effects; 
    // �̗�UP���̃G�t�F�N�g�`�掞��
    float m_healthUpEffectRenderTime;
     // ���xUP���̃G�t�F�N�g�`�掞��
    float m_speedUpEffectRenderTime;
    // �U�鑬�xUP���̃G�t�F�N�g�`�掞��
    float m_swingSpeedEffectRenderTime; 
    // ��UP���̃G�t�F�N�g�`�掞��
    float m_powerUpEffectRenderTime; 
    // ���xUP�G�t�F�N�g���L����
    bool m_speedUpEffectIsActive;
    // �̗�UP�G�t�F�N�g���L����
    bool m_healthUpEffectIsActive; 
    // ��UP�G�t�F�N�g���L����
    bool m_powerUpEffectIsActive;
    // �U�鑬�xUP�G�t�F�N�g���L����
    bool m_swingSpeedEffectIsActive; 

    //  ���ߍ���yyy�֐�
private:

    /// <summary>
    /// �v���C���[�̃X�e�[�^�X�ω��ɉ����āA�G�t�F�N�g�����Z�b�g����
    /// </summary>
    void ResetEffectsIfPlayerStatusChanged();

    /// <summary>
    /// �v���C���[��HP�ቺ��Ԃ��`�F�b�N���A�^�X�N�ɒǉ�����
    /// </summary>
    void CheckAndAddPlayerHPCrisisEffect();

    /// <summary>
    /// �v���C���[�̃X�e�[�^�X�㏸�������s��
    /// </summary>
    /// <param name="timer">�^�C�}�[</param>
    void HandlePlayerStatusUpgrade(const DX::StepTimer& timer);

    /// <summary>
    /// �v���C���[�̃X�e�[�^�X�㏸�������s��
    /// </summary>
    /// <param name="timer">�^�C�}�[</param>
    /// <param name="isEffectActive">�G�t�F�N�g���L�����ǂ���</param>
    /// <param name="effectRenderTime">�G�t�F�N�g�̕`�掞��</param>
    /// <param name="effectType">�G�t�F�N�g�̃^�C�v</param>
    void HandleStatusUpgrade(const DX::StepTimer& timer , bool isUpgraded, bool& isEffectActive, float& effectRenderTime, PostEffect::PostEffectType effectType);

    /// <summary>
    /// �o�^���ꂽ�G�t�F�N�g���X�V����
    /// </summary>
    /// <param name="timer">�^�C�}�[</param>
    void UpdateRegisteredEffects(const DX::StepTimer& timer);
};