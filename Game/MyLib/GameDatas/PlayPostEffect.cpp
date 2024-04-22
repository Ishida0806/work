//
//		File Name �F PlayPostEffect.cpp
//		Production�F 2023/1/10
//		Author�@�@�F �Γc ����	
// 
//		��ʌ��ʂ��܂Ƃ߂��N���X
//
#include "pch.h"
#include "PlayPostEffect.h"

#include "Game/MyLib/Scenes/PlayScene/UI/PlayerHPBar.h"
#include "Game/MyLib/Scenes/PlayScene/Object/Player.h"

//	�`�掞��
const float PlayPostEffect::RENDER_EFFECT_TIME = 0.82f;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="playerHPBar">�̗̓o�[</param>
/// <param name="player">�v���C���[</param>
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
/// �f�X�g���N�^
/// </summary>
PlayPostEffect::~PlayPostEffect()
{
}


/// <summary>
///	����������
/// </summary>
void PlayPostEffect::Initialize()
{
	m_effects.push_back(std::make_unique<PlayerHPCrisisEffect>());
	m_effects.push_back(std::make_unique<PlayerCureEffect>());
	m_effects.push_back(std::make_unique<PlayerSpeedEffect>());
	m_effects.push_back(std::make_unique<PlayerPowerEffect>());
	m_effects.push_back(std::make_unique<PlayerSwingSpeedEffect>());

	//  ������
	for (const auto& effect : m_effects)
		effect->Initialize();
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void PlayPostEffect::Update(const DX::StepTimer& timer)
{
    // �o�ߎ��Ԃ��X�V
    m_elapsedTime += static_cast<float>(timer.GetElapsedSeconds());

    // �v���C���[�̏�ԕω����`�F�b�N���A�G�t�F�N�g�����Z�b�g
    ResetEffectsIfPlayerStatusChanged();

    // �v���C���[��HP�ቺ��Ԃ��`�F�b�N���A�^�X�N�ɒǉ�
    CheckAndAddPlayerHPCrisisEffect();

    // �v���C���[�̃X�e�[�^�X�㏸����
    HandlePlayerStatusUpgrade(timer);

    // �^�X�N�ɓo�^���ꂽ�G�t�F�N�g���X�V
    UpdateRegisteredEffects(timer);

    // �^�X�N���N���A
    m_task.clear();
}

/// <summary>
/// �v���C���[�̏�ԕω����`�F�b�N���A�G�t�F�N�g�����Z�b�g
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
            // �s���`�G�t�F�N�g�͗�O
            if (effect->GetEffectType() == PostEffect::PostEffectType::PlayerHPCrisis) continue;
            effect->ResetColorAndTime();
        }
    }
}

/// <summary>
/// �v���C���[��HP�ቺ��Ԃ��`�F�b�N���A�^�X�N�ɒǉ�����
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
            // �s���`�G�t�F�N�g�ȊO�͍X�V���Ȃ�
            if (effect->GetEffectType() != PostEffect::PostEffectType::PlayerHPCrisis) continue;
            effect->ResetLerpColor();
        }
    }
}

/// <summary>
/// �v���C���[�̃X�e�[�^�X�㏸�������s��
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void PlayPostEffect::HandlePlayerStatusUpgrade(const DX::StepTimer& timer)
{
    HandleStatusUpgrade(timer , m_player->ChooseHealthUP(),      m_healthUpEffectIsActive,   m_healthUpEffectRenderTime,    PostEffect::PostEffectType::HealthUP);
    HandleStatusUpgrade(timer , m_player->ChooseSpeedUP(),       m_speedUpEffectIsActive,    m_speedUpEffectRenderTime,     PostEffect::PostEffectType::SpeedUP);
    HandleStatusUpgrade(timer , m_player->ChooseSwingSpeedUP(),  m_swingSpeedEffectIsActive, m_swingSpeedEffectRenderTime,  PostEffect::PostEffectType::SwingSpeedUP);
    HandleStatusUpgrade(timer , m_player->ChoosePowerUP(),       m_powerUpEffectIsActive,    m_powerUpEffectRenderTime,     PostEffect::PostEffectType::PowerUP);
}

/// <summary>
/// �v���C���[�̃X�e�[�^�X�㏸�������s��
/// </summary>
/// <param name="timer">�^�C�}�[</param>
/// <param name="isEffectActive">�G�t�F�N�g���L�����ǂ���</param>
/// <param name="effectRenderTime">�G�t�F�N�g�̕`�掞��</param>
/// <param name="effectType">�G�t�F�N�g�̃^�C�v</param>
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

        //  �o�ߎ��Ԃ��z���Ă�����t���O��܂�A�������^�[��
        if (effectRenderTime > RENDER_EFFECT_TIME)
        {
            isEffectActive = false;

            return;
        }
        //  �����܂ŗ��ꂽ��܂��\������
        m_task.push_back(effectType);
    }
}

/// <summary>
/// �o�^���ꂽ�G�t�F�N�g���X�V����
/// </summary>
/// <param name="timer">�^�C�}�[</param>
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
/// �`��̃^�C�v
/// </summary>
void PlayPostEffect::Draw()
{
	//	�G�t�F�N�g�̕`��
	for (const auto& effect : m_effects)
	{
		effect->Draw();
	}
}
