//
//		File Name �F FadeCamera.h
//		Production�F 2023/9/07
//		Author�@�@�F �Γc ����	
//
#pragma once
#include "Game/MyLib/Camera/Camera.h"

class FadeCamera : public Camera::ICAMERASTATE
{
	//	�萔
public:

	// �����_�ւ̋����̍����ɑ΂��銄���E�t�F�[�h
	static const float FADE_RATE;

	//	�ϐ�
private:



	//	�֐�
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	FadeCamera();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~FadeCamera();

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