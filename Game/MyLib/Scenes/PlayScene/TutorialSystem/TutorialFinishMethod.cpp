
#include "pch.h"
#include "TutorialFinishMethod.h"

#include "Game/MyLib/Scenes/PlayScene/PlayScene.h"

//	�ڕW�I������
const float TutorialFinishMethod::FINISH_TARGET_SECONDS	= 3.4f;

/// <summary>
/// �R���X�g���N�^
/// </summary>
TutorialFinishMethod::TutorialFinishMethod()
	:
	m_elapsedTime(0.0f)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
TutorialFinishMethod::~TutorialFinishMethod()
{
}

/// <summary>
/// ����ւ��O�ɌĂяo��
/// </summary>
/// <param name="finiteStateMachine">�I�[�i�[</param>
void TutorialFinishMethod::Enter(TutorialSystem::TUTORIALSTATE* finiteStateMachine)
{

}

/// <summary>
/// ���s����
/// </summary>
/// <param name="finiteStateMachine">�I�[�i�[<</param>
/// <param name="elapsedTime">�o�ߎ���</param>
void TutorialFinishMethod::Execute(TutorialSystem::TUTORIALSTATE* finiteStateMachine, const DX::StepTimer& timer)
{
	//	�o�ߎ���
	m_elapsedTime += static_cast<float>(timer.GetElapsedSeconds());

	if (m_elapsedTime >= FINISH_TARGET_SECONDS)
	{
		//	�`���[�g���A���I��
		finiteStateMachine->GetOwner()->GetPlayScene()->FinishTutorial();
	}
}

/// <summary>
/// �ޏo���̏���
/// </summary>
/// <param name="finiteStateMachine">�I�[�i�[</param>
void TutorialFinishMethod::Exit(TutorialSystem::TUTORIALSTATE* finiteStateMachine)
{
	UNREFERENCED_PARAMETER(finiteStateMachine);
}
