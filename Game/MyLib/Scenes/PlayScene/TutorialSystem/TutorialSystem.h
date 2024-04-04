//
//		File Name �F TutorialSystem.h
//		Production�F 2024/4/04
//		Author�@�@�F �Γc ����	
//	
#pragma once

class TutorialSystem
{

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	TutorialSystem();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~TutorialSystem();

	/// <summary>
	/// ����������
	/// </summary>
	void Initialize();
	
	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="timer">�^�C�}�[</param>
	void Update(const DX::StepTimer& timer);

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Render();

	/// <summary>
	/// �I������
	/// </summary>
	void Finalize();
};