//
//		File Name �F ShakeCamera.h
//		Production�F 2023/9/07
//		Author�@�@�F �Γc ����	
//
#pragma once
#include "Game/MyLib/Camera/Camera.h"

class ShakeCamera : public Camera::ICAMERASTATE
{
	//	�萔
public:

	//	�v���C���[���_���[�W���󂯂��ۂɗh�炷�U�ꕝ
	static const float SHAKE_CAMERA;
	//	�h�炷����
	static const float SHAKE_TIME;
	// �J�����̈ʒu�ւ̋����ɑ΂��銄��
	static const float EYE_RATE;
	// �����_�ւ̋����̍����ɑ΂��銄��
	static const float TARGET_RATE;

	//	�ϐ�
private:

	//	�o�ߎ���
	float m_elapsedTime;

	//	�֐�
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	ShakeCamera();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~ShakeCamera();

	/// <summary>
	/// ����ւ��O�ɌĂяo��
	/// </summary>
	/// <param name="finiteStateMachine">�I�[�i�[</param>
	void Enter(Camera::CAMERASTATE* finiteStateMachine) override;

	/// <summary>
	/// ���s����
	/// </summary>
	/// <param name="finiteStateMachine">�I�[�i�[<</param>
	/// <param name="elapsedTime">�o�ߎ���</param>
	void Execute(Camera::CAMERASTATE* finiteStateMachine, const DX::StepTimer& timer) override;

	/// <summary>
	/// �ޏo���̏���
	/// </summary>
	/// <param name="finiteStateMachine">�I�[�i�[</param>
	void Exit(Camera::CAMERASTATE* finiteStateMachine) override;
};