//
//		File Name �F TutorialFinishMethod.h
//		Production�F 2024/4/04
//		Author�@�@�F �Γc ����	
//
#pragma once
#include "Game/MyLib/Scenes/PlayScene/TutorialSystem/TutorialSystem.h"

class TutorialFinishMethod : public TutorialSystem::ITUTORIALSTATE
{
	//	�萔
public:

	//	�ڕW�I������
	static const float FINISH_TARGET_SECONDS;

	//	�ϐ�
private:

	//	�o�ߎ���
	float m_elapsedTime;

	//	�֐�
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	TutorialFinishMethod();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~TutorialFinishMethod();

	/// <summary>
	/// ����ւ��O�ɌĂяo��
	/// </summary>
	/// <param name="finiteStateMachine">�I�[�i�[</param>
	void Enter(TutorialSystem::TUTORIALSTATE* finiteStateMachine) override;

	/// <summary>
	/// ���s����
	/// </summary>
	/// <param name="finiteStateMachine">�I�[�i�[<</param>
	/// <param name="elapsedTime">�o�ߎ���</param>
	void Execute(TutorialSystem::TUTORIALSTATE* finiteStateMachine, const DX::StepTimer& timer) override;

	/// <summary>
	/// �ޏo���̏���
	/// </summary>
	/// <param name="finiteStateMachine">�I�[�i�[</param>
	void Exit(TutorialSystem::TUTORIALSTATE* finiteStateMachine) override;
};