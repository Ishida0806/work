//
//		File Name �F PlayInfo.h
//		Production�F 2023/10/17
//		Author�@�@�F �Γc ����
//
//		�v���C�V�[���ŋN�����������L�^����
//		
#include "pch.h"
#include "PlayInfo.h"

//	�|�C���^�[
std::unique_ptr<PlayInfo> PlayInfo::m_playInfo = nullptr;
//	�X�R�A�̍ő�l
const int PlayInfo::MAX_SCORE = 9999;

/// <summary>
/// �v���C�C���t�H���擾����
/// </summary>
/// <returns></returns>
PlayInfo* const PlayInfo::GetInstance()
{
	//	���݂��Ă��Ȃ��Ȃ�쐬
	if (!m_playInfo)
	{
		m_playInfo.reset(new PlayInfo());		
	}

	//	�A�h���X��Ԃ�
	return m_playInfo.get();
}

/// <summary>
/// �R���X�g���N�^
/// </summary>
PlayInfo::PlayInfo()
	:m_level(0),
	m_score(0),
	m_normalEnemyKnockNum(0),
	m_tackleEnemyKnockNum(0),
	m_bossEnemyKnockNum(0),
	m_elapsedTime(0.0f)
{
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayInfo::~PlayInfo()
{
}

/// <summary>
/// ���������s��
/// </summary>
void PlayInfo::Initialize()
{
	m_level = 0;
	m_score = 0;
	m_normalEnemyKnockNum = 0;
	m_tackleEnemyKnockNum = 0;
	m_bossEnemyKnockNum = 0;
	m_elapsedTime = 0.0f;
}

/// <summary>
/// �ʏ�G�̌��j�����v���X����
/// </summary>
void PlayInfo::KnockNormal()
{
	m_normalEnemyKnockNum++;
}

/// <summary>
/// �ˌ��G�̌��j�����v���X����
/// </summary>
void PlayInfo::KnockTackle()
{
	m_tackleEnemyKnockNum++;
}

/// <summary>
/// �{�X�G�̌��j�����v���X����
/// </summary>
void PlayInfo::KnockBoss()
{
	m_bossEnemyKnockNum++;
}

/// <summary>
/// �X�R�A���グ��
/// </summary>
/// <param name="score">���X�R�A�H</param>
void PlayInfo::UpScore(const int& score)
{
	m_score += score;

	//�X�R�A���I�[�o�[���Ă��琮����
	m_score = Utility::Clamp(m_score, 0, MAX_SCORE);
}

/// <summary>
/// �o�ߎ��Ԃ�ݒ肷��
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void PlayInfo::SetElapsedTime(const float& elapsedTime)
{
	m_elapsedTime = elapsedTime;
}
