//
//		File Name �F PlayerExperiencePoint.cpp
//		Production�F 2023/11/30
//		Author�@�@�F �Γc ����	
// 
//		�o���l���Ǘ��擾����
//	
#include "pch.h"
#include "PlayerExperiencePoint.h"

#include "../Player.h"


//	�v���C���[�̍ő僌�x��
const int PlayerExperiencePoint::MAX_PLAYER_LEVEL = 10;
//	�ŏ��̌o���l
const int PlayerExperiencePoint::FIRST_LEVEL_EXP  = 5;
//	�o���l�̑�����
const int PlayerExperiencePoint::INCREASE_EXP	  = 12;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="player">�v���C���[</param>
PlayerExperiencePoint::PlayerExperiencePoint(Player* player)
	:m_player(player),
	m_experiencePoint(0),
	m_needExperiencePoint(0),
	m_surplusExperiencePoint(0)
{
	m_needExperiencePoint = FIRST_LEVEL_EXP;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayerExperiencePoint::~PlayerExperiencePoint()
{
}

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void PlayerExperiencePoint::Update(const DX::StepTimer& timer)
{
	UNREFERENCED_PARAMETER(timer);

	//	�K�v�o���l�l�𒴂��Ă�����␳����
	ClampEXP();

	//	���x�����擾����
	int level = m_player->GetPlayerLevel();

	//	�ő僌�x���ɒB������A��
	if (level >= MAX_PLAYER_LEVEL)	 return;


#ifdef _DEBUG
	m_experiencePoint++; 
#endif // _DEBUG



	//	���x���A�b�v�ɕK�v�Ȍo���l�ɍs���Ă��邩�m�F����
	if (m_experiencePoint >= m_needExperiencePoint)
	{
		//	SE���Đ�����
		AudioManager::GetInstance()->PlaySoundEffectSE(L"levelUP");
		//	�v���C��[�̃��x�����オ����
		m_player->UpLevel();
		//	���݂̌o���l�̓��Z�b�g����
		m_experiencePoint	   = 0;
		//	���̖ڕW�l��ݒ肷��
		m_needExperiencePoint += INCREASE_EXP;
	}

	//	�]�蕪����������n��
	if (m_surplusExperiencePoint > 0)
	{
		m_experiencePoint += m_surplusExperiencePoint;
		m_surplusExperiencePoint = 0;
	}
}

/// <summary>
/// �o���l��␳����
/// </summary>
void PlayerExperiencePoint::ClampEXP()
{
	//	�K�v�o���l�l�𒴂��Ă�����␳����
	if (m_experiencePoint > m_needExperiencePoint)
	{
		//	�o���l�𒴂��Ă�����]�蕪����������
		m_surplusExperiencePoint += m_experiencePoint - m_needExperiencePoint;
		//	�����������璴���Ȃ��悤�ɕ␳����
		m_experiencePoint = m_needExperiencePoint;
	}
}

/// <summary>
/// �o���l���擾����
/// </summary>
/// <param name="exPoint">�擾�����o���l��</param>
void PlayerExperiencePoint::SetExperiencePoint(const int& exPoint)
{
	m_experiencePoint += exPoint;

	ClampEXP();
}
