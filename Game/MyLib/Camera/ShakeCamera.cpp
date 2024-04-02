//
//		File Name �F Camera.cpp
//		Production�F 2023/6/09
//		Author�@�@�F �Γc ����	
// 
//		�Q�[���J�����̎������s�����N���X
//
//////////////////////////////////////////////////////////////////////////
//						Camera�̃N���X							  // 
//////////////////////////////////////////////////////////////////////////
#include "pch.h"
#include "ShakeCamera.h"

//	�v���C���[���_���[�W���󂯂��ۂɗh�炷�U�ꕝ
const float ShakeCamera::SHAKE_CAMERA	  = 0.22f;
//	�h�炷����
const float ShakeCamera::SHAKE_TIME		  = 0.5f;
//	�J�����̈ʒu�ւ̋����ɑ΂��銄��
const float ShakeCamera::EYE_RATE		  = 0.025f;
//	�����_�ւ̋����ɑ΂��銄��
const float ShakeCamera::TARGET_RATE	  = 0.95f;

/// <summary>
/// �R���X�g���N�^
/// </summary>
ShakeCamera::ShakeCamera()
	:m_elapsedTime(0.0f)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ShakeCamera::~ShakeCamera()
{
}

/// <summary>
/// ����ւ��O�ɌĂяo��
/// </summary>
/// <param name="finiteStateMachine">�I�[�i�[</param>
void ShakeCamera::Enter(Camera::CAMERASTATE* finiteStateMachine)
{
	//	������
	m_elapsedTime = 0.0f;

	UNREFERENCED_PARAMETER(finiteStateMachine);
}

/// <summary>
/// ���s����
/// </summary>
/// <param name="finiteStateMachine">�I�[�i�[<</param>
/// <param name="elapsedTime">�o�ߎ���</param>
void ShakeCamera::Execute(Camera::CAMERASTATE* finiteStateMachine, const DX::StepTimer& timer)
{
	//	�o�ߎ��Ԃ𑫂�
	m_elapsedTime += static_cast<float>(timer.GetElapsedSeconds());
	//	�J����
	Camera* camera = finiteStateMachine->GetOwner();

	if (camera->IsShake())	
	{
		camera->CompletedShake();
		m_elapsedTime = 0.0f;
	}

	//	�^�[�Q�b�g���擾����
	DirectX::SimpleMath::Vector3 orijinalTarget = camera->GetOrijinalTargetPosition();
	//	�^�[�Q�b�g�̒Ǐ]
	camera->SetTargetPosition(DirectX::SimpleMath::Vector3::Lerp(camera->GetTargetPosition(), orijinalTarget, TARGET_RATE));
	camera->SetEyePosition(DirectX::SimpleMath::Vector3::Lerp(camera->GetEyePosition(),		  orijinalTarget, EYE_RATE));

	//	�^�[�Q�b�g���擾����
	DirectX::SimpleMath::Vector3 target = camera->GetTargetPosition();
	//	�^�[�Q�b�g��h�炷
	target.x += Utility::CreateRandom(-SHAKE_CAMERA, SHAKE_CAMERA);
	target.z += Utility::CreateRandom(-SHAKE_CAMERA, SHAKE_CAMERA);
	//	�J������ݒ肷��
	camera->SetTargetPosition(target);

	if (m_elapsedTime > SHAKE_TIME)
	{
		//	�ς���
		finiteStateMachine->RequestTransition(Camera::CameraState::Idle);
	}
}

/// <summary>
/// �ޏo���̏���
/// </summary>
/// <param name="finiteStateMachine">�I�[�i�[</param>
void ShakeCamera::Exit(Camera::CAMERASTATE* finiteStateMachine)
{
	UNREFERENCED_PARAMETER(finiteStateMachine);
	//	������
	m_elapsedTime = 0.0f;
}
