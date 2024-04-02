//
//		File Name �F WinCamera.h
//		Production�F 2023/9/07
//		Author�@�@�F �Γc ����	
//
#pragma once
#include "Game/MyLib/Camera/Camera.h"

class WinCamera : public Camera::ICAMERASTATE
{
	//	�萔
public:

	// �J�����̈ʒu�ւ̋����ɑ΂��銄��
	static const float EYE_RATE;
	// �����_�ւ̋����̍����ɑ΂��銄��
	static const float TARGET_RATE;


	//	�ϐ�
private:



	//	�֐�
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	WinCamera();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~WinCamera();

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