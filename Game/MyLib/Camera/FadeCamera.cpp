//
//		File Name �F FadeCamera.cpp
//		Production�F 2023/6/09
//		Author�@�@�F �Γc ����	
// 
//		�Q�[���J�����̎������s�����N���X
//
//////////////////////////////////////////////////////////////////////////
//						Camera�̃N���X									// 
//////////////////////////////////////////////////////////////////////////
#include "pch.h"
#include "FadeCamera.h"

// �����_�ւ̋����̍����ɑ΂��銄���E�t�F�[�h
const float FadeCamera::FADE_RATE = 0.008f;

/// <summary>
/// �R���X�g���N�^
/// </summary>
FadeCamera::FadeCamera()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
FadeCamera::~FadeCamera()
{
}

/// <summary>
/// ����ւ��O�ɌĂяo��
/// </summary>
/// <param name="finiteStateMachine">�I�[�i�[</param>
void FadeCamera::Enter(Camera::CAMERASTATE* finiteStateMachine)
{
	UNREFERENCED_PARAMETER(finiteStateMachine);
}

/// <summary>
/// ���s����
/// </summary>
/// <param name="finiteStateMachine">�I�[�i�[<</param>
/// <param name="elapsedTime">�o�ߎ���</param>
void FadeCamera::Execute(Camera::CAMERASTATE* finiteStateMachine, const DX::StepTimer& timer)
{
	UNREFERENCED_PARAMETER(timer);
	//	�e
	Camera* camera = finiteStateMachine->GetOwner();

	DirectX::SimpleMath::Vector3 target = finiteStateMachine->GetOwner()->GetOrijinalTargetPosition();
	//	�Ǐ]������
	camera->SetTargetPosition(DirectX::SimpleMath::Vector3::Lerp(camera->GetTargetPosition(), target, FADE_RATE));
	camera->SetEyePosition(DirectX::SimpleMath::Vector3::Lerp(camera->GetEyePosition(), target, FADE_RATE));

	//	�t�F�[�h��Ԃ��I��������ԑJ��
	if (!camera->IsFade())
	{
		//	�ς���
		finiteStateMachine->RequestTransition(Camera::CameraState::Idle);
	}
}

/// <summary>
/// �ޏo���̏���
/// </summary>
/// <param name="finiteStateMachine">�I�[�i�[</param>
void FadeCamera::Exit(Camera::CAMERASTATE* finiteStateMachine)
{
	UNREFERENCED_PARAMETER(finiteStateMachine);
}
