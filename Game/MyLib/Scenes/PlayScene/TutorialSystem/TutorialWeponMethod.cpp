//
//		File Name �F TutorialWeponMethod.cpp
//		Production�F 2024/4/04
//		Author�@�@�F �Γc ����	
// 
//		�����U�鑀�����
//
#include "pch.h"
#include "TutorialWeponMethod.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
TutorialWeponMethod::TutorialWeponMethod()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
TutorialWeponMethod::~TutorialWeponMethod()
{
}

/// <summary>
/// ����ւ��O�ɌĂяo��
/// </summary>
/// <param name="finiteStateMachine">�I�[�i�[</param>
void TutorialWeponMethod::Enter(TutorialSystem::TUTORIALSTATE* finiteStateMachine)
{

}

/// <summary>
/// ���s����
/// </summary>
/// <param name="finiteStateMachine">�I�[�i�[<</param>
/// <param name="elapsedTime">�o�ߎ���</param>
void TutorialWeponMethod::Execute(TutorialSystem::TUTORIALSTATE* finiteStateMachine, const DX::StepTimer& timer)
{
	//	�}�E�X
	auto mouse = MyLib::InputSystem::GetInstance()->GetStateTracker();

	if (mouse->leftButton)
	{
		//	���̉摜�K�C�h��ݒ肷��
		finiteStateMachine->GetOwner()->SetGuideTexture(MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"TutorialGuide03"));
		//	���̏�Ԃ����߂�
		finiteStateMachine->RequestTransition(TutorialSystem::TutorialState::KillEnemyMethod);
	}	
}

/// <summary>
/// �ޏo���̏���
/// </summary>
/// <param name="finiteStateMachine">�I�[�i�[</param>
void TutorialWeponMethod::Exit(TutorialSystem::TUTORIALSTATE* finiteStateMachine)
{
}
