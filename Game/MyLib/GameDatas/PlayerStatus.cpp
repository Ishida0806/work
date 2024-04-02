//
//		File Name �F PlayerStatus.cpp
//		Production�F 2023/1/30
//		Author�@�@�F �Γc ����	
// 
//		�v���C���[�̃X�e�[�^�X�̊Ǘ��N���X
//	
#include "pch.h"
#include "PlayerStatus.h"

//	�v���C���[�̍ŏ��̃��x��
const int PlayerStatus::FIRST_LEVEL		  = 1;
//	�v���C���[�̗�
const int PlayerStatus::FIRST_POWER		  = 1;
//	�񕜂̒l
const int PlayerStatus::RECOVERY_VALUE	  = 10;
//	���G����
const float PlayerStatus::INVINCIBLE_TIME = 0.9f;
//	���x
const float PlayerStatus::FIRST_SPEED	  = 0.08f;
//	�񕜂��\����
const float PlayerStatus::RECOVERY_TIME	  = 5.5f;
//	�p���[�A�b�v�^�C��
const float PlayerStatus::POWER_UP_TIME	  = 15.0f;

/// <summary>
///  �R���X�g���N�^
/// </summary>
/// <param name="player">�v���C���[</param>
/// <param name="health">�̗�</param>
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
/// �f�X�g���N�^
/// </summary>
PlayerStatus::~PlayerStatus()
{
}

/// <summary>
/// ����������
/// </summary>
void PlayerStatus::Initialize()
{
	//	���x�����߂�
	m_speed = FIRST_SPEED;
	//	�v���C���[�̌o���l���쐬����
	m_playerEP = std::make_unique<PlayerExperiencePoint>(m_player);
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void PlayerStatus::Update(const DX::StepTimer& timer)
{
	//	�o���l��Ԃ��m�F����
	m_playerEP->Update(timer);
	// ���x���A�b�v�����t���O�����ɖ߂�
	CheckLevelUP();
	// ���Ԍo�߂ő̗͂̉񕜂��s��
	Recovery(timer);
	//	���G�ɂȂ��Ă����玞�Ԍo�߂Ŗ߂�
	CheckInvincibility(timer);
	//	�p���[�A�b�v��Ԃ̐������m�F����
	CheckPowerUP(timer);
}

/// <summary>
/// �v���C���[���A�C�e�����擾����
/// </summary>
void PlayerStatus::GetPowerUPItem()
{
	m_powerUPTime = 0.0f;
	m_isPowerUP = true;
}

/// <summary>
/// �v���C���[���񕜃A�C�e�����擾����
/// </summary>
void PlayerStatus::GetRecoveryItem()
{
	//	�񕜂���
	m_health += RECOVERY_VALUE * 2;
	//	�ő�l�𒴂��Ȃ��悤��
	m_health = Utility::Clamp(m_health, 0, m_maxHealth);
	//	�񕜎��Ԃ̓��Z�b�g����
	m_lifeRerecoveryTime = 0.0f;
}


/// <summary>
/// ���x���A�b�v�����t���O�����ɖ߂�
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
/// �p���[�A�b�v��Ԃ̐������m�F����
/// </summary>
void PlayerStatus::CheckPowerUP(const DX::StepTimer& timer)
{
	if (m_isPowerUP)
	{
		//	�U���͂�1������
		m_attckPower = FIRST_POWER;
		//	�o�ߎ��Ԃ𑫂�
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
/// ���G���ǂ������m�F����
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void PlayerStatus::CheckInvincibility(const DX::StepTimer& timer)
{
	//	���Ԍo�߂Ŗ��G��Ԃ�����
	if (!m_isInvincible)	return;

	//	���G���Ԃ��擾����
	m_invincibleTime += static_cast<float>(timer.GetElapsedSeconds());

	//	���G���Ԓ��Ȃ�A��	
	if (m_invincibleTime >= INVINCIBLE_TIME)	return;

	m_isInvincible = false;
	m_invincibleTime = 0.0f;
}

/// <summary>
/// ���Ԍo�߂ő̗͂̉񕜂��s��
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void PlayerStatus::Recovery(const DX::StepTimer& timer)
{
	// �����ő匒�N�l�ȏ�ł���΁A�񕜏������s��Ȃ�
	if (m_maxHealth <= m_health)
		return;

	// �񕜎��� �Ɍo�ߎ��Ԃ����Z
	m_lifeRerecoveryTime += static_cast<float>(timer.GetElapsedSeconds());

	// �o�ߎ��Ԉȏ�o�߂����ꍇ�A�񕜏��������s
	if (m_lifeRerecoveryTime >= RECOVERY_TIME)
	{
		// �o�ߎ��Ԃ����Z�b�g
		m_lifeRerecoveryTime = 0.0f;

		// �����̗͂��񕜂����Ă��ő匒�N�l�𒴂��Ȃ��ꍇ
		if (m_health + RECOVERY_VALUE <= m_maxHealth)
		{
			// �̗͒l���񕜂�����
			m_health += RECOVERY_VALUE;
		}
		else
		{
			// �ő�̗͒l�ɐݒ�
			m_health = m_maxHealth;
		}
		//	�w�肳�ꂽSE�𗬂�
		AudioManager::GetInstance()->PlaySoundEffectSE(L"RecoverSE01");
	}
}

/// <summary>
/// �̗͂��[���ɂ���
/// </summary>
void PlayerStatus::HealthZero()
{
	m_health = 0;
}

/// <summary>
/// ���G�ɂ���
/// </summary>
/// <param name="flag">�t���O</param>
void PlayerStatus::SetInvincible(const bool& flag)
{
	m_isInvincible = flag;
}

/// <summary>
/// �_���[�W��Ԃ�ݒ肷��
/// </summary>
/// <param name="flag"></param>
void PlayerStatus::SetDamegeCondition(const bool& flag)
{
	m_isDamege = flag;
}

/// <summary>
///	�_���[�W��ݒ肷��
/// </summary>
/// <param name="damege">�_���[�W</param>
void PlayerStatus::SetDamege(const int& damege)
{
	m_health -= damege;
	//	�_���[�W��0�ȏ�Ȃ��Ԃ�����
	if (damege != 0)
	{
		m_lifeRerecoveryTime = 0.0f;
		m_isInvincible = true;
		m_isDamege = true;
	}
}

/// <summary>
/// �̗͂̍ő�l�𑝂₷
/// </summary>
/// <param name="value">������</param>
void PlayerStatus::UpMaxHP()
{
	m_maxHealth += 20;
	//	�̗͂��I�΂ꂽ
	m_healthUP = true;
}

/// <summary>
/// ���x�𑝂₷
/// </summary
void PlayerStatus::UpSpeed()
{
	m_speed += 0.01f;
	//	���x���I�΂ꂽ
	m_speedUP = true;
}

/// <summary>
/// �͂��オ��
/// </summary>
void PlayerStatus::UpPower()
{
	m_power++;
	//	�p���[���I�΂ꂽ
	m_powerUP = true;
}

/// <summary>
///	���x�����オ����
/// </summary>
void PlayerStatus::UpLevel()
{
	m_level++;
}