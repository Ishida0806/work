//
//		File Name �F IdleCamera.cpp
//		Production�F 2023/6/09
//		Author�@�@�F �Γc ����	
// 
//		�Q�[���J�����̎������s�����N���X
//
//////////////////////////////////////////////////////////////////////////
//						Camera�̃N���X									// 
//////////////////////////////////////////////////////////////////////////
#include "pch.h"
#include "IdleCamera.h"

//	�J�����̈ʒu�ւ̋����ɑ΂��銄��
const float IdleCamera::EYE_RATE = 0.03f;
//	�����_�ւ̋����ɑ΂��銄��
const float IdleCamera::TARGET_RATE = 0.1f;

/// <summary>
/// �R���X�g���N�^
/// </summary>
IdleCamera::IdleCamera()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
IdleCamera::~IdleCamera()
{
}

/// <summary>
/// ����ւ��O�ɌĂяo��
/// </summary>
/// <param name="finiteStateMachine">�I�[�i�[</param>
void IdleCamera::Enter(Camera::CAMERASTATE* finiteStateMachine)
{
	UNREFERENCED_PARAMETER(finiteStateMachine);
}

/// <summary>
/// ���s����
/// </summary>
/// <param name="finiteStateMachine">�I�[�i�[<</param>
/// <param name="elapsedTime">�o�ߎ���</param>
void IdleCamera::Execute(Camera::CAMERASTATE* finiteStateMachine, const DX::StepTimer& timer)
{
	UNREFERENCED_PARAMETER(timer);
	//	�J�������擾����
	Camera* camera = finiteStateMachine->GetOwner();

	//	�_���[�W���[�h�Ȃ�h�炷���[�h��
	if (finiteStateMachine->GetOwner()->IsShake())
	{
		//	�ς���
		finiteStateMachine->RequestTransition(Camera::CameraState::Shake);
		//	���[�h�ύX������
		finiteStateMachine->GetOwner()->CompletedShake();
	}
	//	�Ǐ]�^�[�Q�b�g
	DirectX::SimpleMath::Vector3 target = finiteStateMachine->GetOwner()->GetOrijinalTargetPosition();
	//	�^�[�Q�b�g�̒Ǐ]
	camera->SetTargetPosition(DirectX::SimpleMath::Vector3::Lerp(camera->GetTargetPosition(), target, TARGET_RATE));
	camera->SetEyePosition(DirectX::SimpleMath::Vector3::Lerp(camera->GetEyePosition(), target, EYE_RATE));
}

/// <summary>
/// �ޏo���̏���
/// </summary>
/// <param name="finiteStateMachine">�I�[�i�[</param>
void IdleCamera::Exit(Camera::CAMERASTATE* finiteStateMachine)
{
	UNREFERENCED_PARAMETER(finiteStateMachine);
}
