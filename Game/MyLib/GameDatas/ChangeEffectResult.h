//
//		File Name �F ChangeEffectResult.h
//		Production�F 2023/1/17
//		Author�@�@�F �Γc ����	
//
#pragma once
#include "ChangeEffect.h"

class ChangeEffectResult : public ChangeEffect
{
	//	�萔
public:

	//	�t�F�[�h�̎���
	static const float						  RESULT_FADE_TIME;
	//	�ޏo�t�F�[�h���̕␳�l
	static const float						  CORRECTION_OUT_FADE;

	//	�ϐ�
private:



	//�֐�
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	ChangeEffectResult();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~ChangeEffectResult() override;

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

	/// <summary>
	/// ���O�̏��������s��
	/// </summary>
	void PreInitialize() override;
};