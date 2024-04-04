
#include "pch.h"
#include "TutorialMovingMethod.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
TutorialMovingMethod::TutorialMovingMethod()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
TutorialMovingMethod::~TutorialMovingMethod()
{
}

/// <summary>
/// ����ւ��O�ɌĂяo��
/// </summary>
/// <param name="finiteStateMachine">�I�[�i�[</param>
void TutorialMovingMethod::Enter(TutorialSystem::TUTORIALSTATE* finiteStateMachine)
{
	m_beforeMousePosition.x = static_cast<float>(MyLib::InputSystem::GetInstance()->GetMouse()->GetState().x);
	m_beforeMousePosition.y = static_cast<float>(MyLib::InputSystem::GetInstance()->GetMouse()->GetState().y);
}

/// <summary>
/// ���s����
/// </summary>
/// <param name="finiteStateMachine">�I�[�i�[<</param>
/// <param name="elapsedTime">�o�ߎ���</param>
void TutorialMovingMethod::Execute(TutorialSystem::TUTORIALSTATE* finiteStateMachine, const DX::StepTimer& timer)
{
	//	���݂̃}�E�X���W
	DirectX::SimpleMath::Vector2 mousePosition;

	//	�X�V
	mousePosition.x = static_cast<float>(MyLib::InputSystem::GetInstance()->GetMouse()->GetState().x);
	mousePosition.y = static_cast<float>(MyLib::InputSystem::GetInstance()->GetMouse()->GetState().y);

	auto input = MyLib::InputSystem::GetInstance()->GetKeyboard()->GetState();

	if ((mousePosition.x != m_beforeMousePosition.x || mousePosition.y != m_beforeMousePosition.y) && (input.A || input.D || input.W || input.S))
	{
		//	���̉摜�K�C�h��ݒ肷��
		finiteStateMachine->GetOwner()->SetGuideTexture(MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"TutorialGuide02"));
		//	���̏�Ԃ����߂�
		finiteStateMachine->RequestTransition(TutorialSystem::TutorialState::WeponMethod);
	}	
}

/// <summary>
/// �ޏo���̏���
/// </summary>
/// <param name="finiteStateMachine">�I�[�i�[</param>
void TutorialMovingMethod::Exit(TutorialSystem::TUTORIALSTATE* finiteStateMachine)
{
}
