//
//		File Name �F DeathCamera.cpp
//		Production�F 2023/6/09
//		Author�@�@�F �Γc ����	
// 
//		�Q�[���J�����̎������s�����N���X
//
//////////////////////////////////////////////////////////////////////////
//						Camera�̃N���X									// 
//////////////////////////////////////////////////////////////////////////
#include "pch.h"
#include "DeathCamera.h"

// �����_�ւ̋����̍����ɑ΂��銄���E�t�F�[�h
const float DeathCamera::FADE_RATE = 0.018f;

/// <summary>
/// �R���X�g���N�^
/// </summary>
DeathCamera::DeathCamera()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
DeathCamera::~DeathCamera()
{
}

/// <summary>
/// ����ւ��O�ɌĂяo��
/// </summary>
/// <param name="finiteStateMachine">�I�[�i�[</param>
void DeathCamera::Enter(Camera::CAMERASTATE* finiteStateMachine)
{
	//	�f�X�J�����ɓ�����
	finiteStateMachine->GetOwner()->InDeathCamera();
}

/// <summary>
/// ���s����
/// </summary>
/// <param name="finiteStateMachine">�I�[�i�[<</param>
/// <param name="elapsedTime">�o�ߎ���</param>
void DeathCamera::Execute(Camera::CAMERASTATE* finiteStateMachine, const DX::StepTimer& timer)
{
	UNREFERENCED_PARAMETER(timer);
	//	�e
	Camera* camera = finiteStateMachine->GetOwner();

	DirectX::SimpleMath::Vector3 target = finiteStateMachine->GetOwner()->GetOrijinalTargetPosition();
	target.y = -3.0f;

	//	�Ǐ]������
	camera->SetTargetPosition(DirectX::SimpleMath::Vector3::Lerp(camera->GetTargetPosition(), target, FADE_RATE));
	camera->SetEyePosition(DirectX::SimpleMath::Vector3::Lerp(camera->GetEyePosition(),		  target, FADE_RATE));
}

/// <summary>
/// �ޏo���̏���
/// </summary>
/// <param name="finiteStateMachine">�I�[�i�[</param>
void DeathCamera::Exit(Camera::CAMERASTATE* finiteStateMachine)
{
	UNREFERENCED_PARAMETER(finiteStateMachine);
}
