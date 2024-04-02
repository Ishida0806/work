//
//		File Name �F PlayerLeftArm.h
//		Production�F 2023/12/27
//		Author�@�@�F �Γc ����	
// 
//		�v���C���[�̊e�p�[�c����
//	
#pragma once
#include "../Player.h"
#include "../PlayeComponent/PlayerComponent.h"

class Player;

class PlayerLeftArm : public PlayerComponent
{
	//	�萔
public:

	//	���S���̉���
	static const DirectX::SimpleMath::Vector3 DEATH_ACCELERATION;
	//	�����ۂ̗h���
	static const float						  CORRECTION_SPEED;
	//	���Ԃ̉����x
	static const float						  ACCELERATION_TIMER;
	//	���W��߂����x
	static const float						  RETURN_SPEED;

	//	�ϐ�
private:

	//	���f��
	DirectX::Model* m_model;
	//	�o�ߎ���
	float			m_elapsedTime;


	//	�֐�
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="root">���[�g</param>
	/// <param name="paren">�e</param>
	PlayerLeftArm(Player* root, Object* parent);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~PlayerLeftArm();

	/// <summary>
	/// ����������
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// ���i���X�V����
	/// </summary>
	/// <param name="timer">�^�C�}�[</param>
	void UpdateParts(const DX::StepTimer& timer) override;

	/// <summary>
	/// ���S�A�j���[�V����
	/// </summary>
	/// <param name="timer">�^�C�}�[</param>
	void DeathAnimation(const DX::StepTimer& timer) override;

	/// <summary>
	/// �����A�j���[�V����
	/// </summary>
	/// <param name="timer">�^�C�}�[</param>
	void WinAnimation(const DX::StepTimer& timer) override;

	/// <summary>
	/// ���f���̕`��
	/// </summary>
	/// <param name="model">���f��</param>
	/// <param name="world">���[���h</param>
	/// <param name="view">�r���[</param>
	/// <param name="proj">�v���W�F�N�V����</param>
	void DrawModel(DirectX::Model* model, const DirectX::SimpleMath::Matrix& world, const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj) override;
};