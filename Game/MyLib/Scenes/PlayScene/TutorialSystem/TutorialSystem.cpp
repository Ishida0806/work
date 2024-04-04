//
//		File Name �F TutorialSystem.cpp
//		Production�F 2024/4/04
//		Author�@�@�F �Γc ����	
// 
//		�`���[�g���A�������̋L�q���܂Ƃ߂��N���X
//	
#include "pch.h"
#include "TutorialSystem.h"

#include "TutorialMovingMethod.h"
#include "TutorialKillEnemyMethod.h"
#include "TutorialWeponMethod.h"
#include "TutorialFinishMethod.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="playScene">�v���C�V�[��</param>
/// <param name="enemyManager">�G�}�l�[�W��</param>
TutorialSystem::TutorialSystem(PlayScene* playScene, EnemyManager* enemyManager)
	:
	m_playScene(playScene),
	m_enemyManager(enemyManager)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
TutorialSystem::~TutorialSystem()
{
}

/// <summary>
/// ����������
/// </summary>
void TutorialSystem::Initialize()
{
	//	�L���X�e�[�g�}�V�[�����쐬
	m_fsm = std::make_unique<TUTORIALSTATE>(this);
	//	�X�e�[�g�̒ǉ�
	m_fsm->RegisterState(TutorialState::MovingMethod, new TutorialMovingMethod());
	m_fsm->RegisterState(TutorialState::KillEnemyMethod, new TutorialKillEnemyMethod());
	m_fsm->RegisterState(TutorialState::WeponMethod, new TutorialWeponMethod());
	m_fsm->RegisterState(TutorialState::FinishMethod, new TutorialFinishMethod());
	//	�n�߂�X�e�[�g��I��
	m_fsm->Start(TutorialState::MovingMethod);
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void TutorialSystem::Update(const DX::StepTimer& timer)
{
	//	�X�V����
	m_fsm->Update(timer);
}

/// <summary>
/// �`�揈��
/// </summary>
void TutorialSystem::Render()
{
}

/// <summary>
/// �I������
/// </summary>
void TutorialSystem::Finalize()
{
}

/// <summary>
/// �`���[�g���A���ē��摜�̐ݒ�
/// </summary>
/// <param name="texture">�摜</param>
inline void TutorialSystem::SetGuideTexture(ID3D11ShaderResourceView* texture)
{
	m_guideTutorialTexture = texture;
}