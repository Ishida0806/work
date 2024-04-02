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
	m_powerUPEffectRenderTime(0.0f),
	m_speedUPEffectRenderTime(0.0f),
	m_healthUPEffectRenderTime(0.0f),
	m_speedUPEffectRenderFlag(false),
	m_healthUPEffectRenderFlag(false),
	m_powerUPEffectRenderFlag(false)
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
	m_effects.push_back(std::make_unique<PlayerPowerffect>());

	//
	for (const auto& effect : m_effects)
		effect->Initialize();
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void PlayPostEffect::Update(const DX::StepTimer& timer)
{
	//	�o�ߎ��Ԃ𑫂�
	m_elapsedTime += static_cast<float>(timer.GetElapsedSeconds());

	//	�������m�F������O�̓z�͏���
	if (m_playerHPBar->IsBad() ||
		m_player->ChooseHealthUP() ||
		m_player->ChooseSpeedUP() ||
		m_player->ChoosePowerUP()
		)
	{
		for (const auto& effect : m_effects)
		{
			//	�s���`�G�t�F�N�g�͗�O
			if (effect->GetEffectType() == PostEffect::PostEffectType::PlayerHPCrisis) continue;

			effect->ResetColorAndTime();
		}
	}

	//	�����𖞂�������^�X�N�ɓ����
	if (m_playerHPBar->IsBad())
	{
		m_task.push_back(PostEffect::PostEffectType::PlayerHPCrisis);
	}
	else
	{	
		for (const auto& effect : m_effects)
		{
			//	�s���`�G�t�F�N�g�ȊO�͋A��
			if (effect->GetEffectType() != PostEffect::PostEffectType::PlayerHPCrisis) continue;
			//	BAD��Ԃł͂Ȃ��̂ŐF�����񂾂񔖂�����
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

	//	�̗͂��オ������𖞂�������
	if (m_healthUPEffectRenderFlag)
	{
		m_task.push_back(PostEffect::PostEffectType::HealthUP);

		m_healthUPEffectRenderTime += static_cast<float>(timer.GetElapsedSeconds());

		if (m_healthUPEffectRenderTime > RENDER_EFFECT_TIME)
		{
			m_healthUPEffectRenderFlag = false;
		}
	}
	//	���x���オ������𖞂�������
	if (m_speedUPEffectRenderFlag)
	{
		m_task.push_back(PostEffect::PostEffectType::SpeedUP);

		m_speedUPEffectRenderTime += static_cast<float>(timer.GetElapsedSeconds());

		if (m_speedUPEffectRenderTime > RENDER_EFFECT_TIME)
		{
			m_speedUPEffectRenderFlag = false;
		}
	}
	//	�͂��オ������𖞂�������
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
	//	�N���A���s��
	m_task.clear();
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
