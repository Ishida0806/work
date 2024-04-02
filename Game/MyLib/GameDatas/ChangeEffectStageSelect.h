//
//		File Name �F ChangeEffectStageSelect.h
//		Production�F 2023/1/17
//		Author�@�@�F �Γc ����	
//
#pragma once
#include "ChangeEffect.h"

class ChangeEffectStageSelect : public ChangeEffect
{
	//	�萔
public:

	//	�t�F�[�h�̎���
	static const float						  STAGE_FADE_TIME;
	//	�h�A�̓������x
	static const float						  DOOR_MOVE_SPEED;
	//	�X�e�[�W�̓��ꂷ��ۂ̃h�A�̉E���̍��W
	static const DirectX::SimpleMath::Vector2 STAGE_TO_RIGHT_DOOR_POSITION;
	//	�X�e�[�W�̓��ꂷ��ۂ̃h�A�̍����̍��W
	static const DirectX::SimpleMath::Vector2 STAGE_TO_LEFT_DOOR_POSITION;
	//	�X�e�[�W�̑ޏꂷ��ۂ̃h�A�̉E���̍��W
	static const DirectX::SimpleMath::Vector2 STAGE_OUT_RIGHT_DOOR_POSITION;
	//	�X�e�[�W�̑ޏꂷ��ۂ̃h�A�̍����̍��W
	static const DirectX::SimpleMath::Vector2 STAGE_OUT_LEFT_DOOR_POSITION;

	//	�ϐ�
private:

	//	���̉E�̍��W
	DirectX::SimpleMath::Vector2			    m_blackRightPos;
	//	���̍��̍��W
	DirectX::SimpleMath::Vector2			    m_blackLeftPos;
	

	//�֐�
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	ChangeEffectStageSelect();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~ChangeEffectStageSelect() override;

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