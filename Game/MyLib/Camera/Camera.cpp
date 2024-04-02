//
//		File Name �F Camera.cpp
//		Production�F 2023/6/09
//		Author�@�@�F �Γc ����	
// 
//		�Q�[���J�����̎������s�����N���X
//
//////////////////////////////////////////////////////////////////////////
//						Camera�̃N���X									// 
//////////////////////////////////////////////////////////////////////////
#include "pch.h"
#include "Camera.h"

#include "Game/MyLib/Scenes/PlayScene/Object/Player.h"
#include "ShakeCamera.h"
#include "DeathCamera.h"
#include "FadeCamera.h"
#include "IdleCamera.h"
#include "WinCamera.h"

//	���������̃I�t�Z�b�g
const DirectX::SimpleMath::Vector3 Camera::DASH_OFFSET_POSITION = DirectX::SimpleMath::Vector3(0.0f, 4.0f, 2.0f);

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="eye">�J�����ʒu</param>
/// <param name="target">���_���W</param>
/// <param name="up">������x�N�g��</param>
/// <param name="player">�v���C���[</param>
Camera::Camera(
	const DirectX::SimpleMath::Vector3& eye, 
	const DirectX::SimpleMath::Vector3& target, 
	const DirectX::SimpleMath::Vector3& up, 
	Player* player)
	:m_eye(eye),
	m_target(target),
	m_up(up),
	m_player(player),
	m_isFade(false),
	m_isDeathCamera(false),
	m_isShake(false)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Camera::~Camera()
{

}

/// <summary>
/// ������
/// </summary>
void Camera::Initialize()
{
	//	�L���X�e�[�g�}�V�[�����쐬
	m_fsm = std::make_unique<CAMERASTATE>(this);
	//	�X�e�[�g�̒ǉ�
	m_fsm->RegisterState(CameraState::Idle,  new IdleCamera());
	m_fsm->RegisterState(CameraState::Shake, new ShakeCamera());
	m_fsm->RegisterState(CameraState::Fade,  new FadeCamera());
	m_fsm->RegisterState(CameraState::Death, new DeathCamera());
	m_fsm->RegisterState(CameraState::Win,	 new WinCamera());
	//	�n�߂�X�e�[�g��I��
	m_fsm->Start(Camera::CameraState::Fade);
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="timer">�^�C�}�[</param>
/// <param name="isFade">�t�F�[�h�����H</param>
void Camera::Update(const DX::StepTimer& timer, const bool& isFade)
{
	//	���炷���W
	DirectX::SimpleMath::Vector3 offsetPos = DASH_OFFSET_POSITION;

	///	�_�b�V�����Ȃ班������𗣂�
	if (!m_player->IsDash())	offsetPos = DirectX::SimpleMath::Vector3::Zero;

	//	�Ǐ]�^�[�Q�b�g�̍X�V
	m_originalTarget = m_player->GetPosition() + offsetPos;
	//	�_���[�W
	m_isShake		 = m_player->IsDamege();
	//	�t�F�[�h
	m_isFade		 = isFade;
	//	�v���C���[�����S������ς���
	if (m_player->IsAlive())		m_fsm->RequestTransition(Camera::CameraState::Death);	
	//	�v���C���[������������ς���
	if (m_player->IsWinAnimation())	m_fsm->RequestTransition(Camera::CameraState::Win);	
	//	�L���X�e�[�g�}�V�[���̍X�V
	m_fsm->Update(timer);
}

/// <summary>
/// �Ǐ]�^�[�Q�b�g��ݒ肷��
/// </summary>
/// <param name="position">���W</param>
void Camera::SetOrijinalTargetPosition(const DirectX::SimpleMath::Vector3& position)
{
	m_originalTarget = position;
}

/// <summary>
/// �^�[�Q�b�g���W��ݒ肷��
/// </summary>
/// <param name="position">���W</param>
void Camera::SetTargetPosition(const DirectX::SimpleMath::Vector3& position)
{
	m_target = position;
}

/// <summary>
/// �A�C��ݒ肷��
/// </summary>
/// <param name="position">���W</param>
void Camera::SetEyePosition(const DirectX::SimpleMath::Vector3& position)
{
	m_eye = position;
}

/// <summary>
/// �h�炷���[�h��߂�
/// </summary>
void Camera::CompletedShake()
{
	m_isShake = false;
}

/// <summary>
/// �f�X�J�������擾
/// </summary>
void Camera::InDeathCamera()
{
	m_isDeathCamera = true;
}