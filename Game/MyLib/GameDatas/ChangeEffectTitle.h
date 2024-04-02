//
//		File Name �F ChangeEffectTitle.h
//		Production�F 2023/1/17
//		Author�@�@�F �Γc ����	
//
#pragma once
#include "ChangeEffect.h"

class ChangeEffectTitle : public ChangeEffect
{
	//	�萔
public:

	//	�t�F�[�h�̎���
	static const float TITLE_FADE_TIME;
	

	//�֐�
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	ChangeEffectTitle();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~ChangeEffectTitle() override;

	/// <summary>
	/// ����������
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// ���̃V�[���ɑJ�ڂ���
	/// </summary>
	void ToChange() override;

	/// <summary>
	/// �V�[���𔲂���
	/// </summary>
	void OutChange() override;

	/// <summary>
	/// �G�t�F�N�g�̕`��
	/// </summary>
	void Draw() override;
};