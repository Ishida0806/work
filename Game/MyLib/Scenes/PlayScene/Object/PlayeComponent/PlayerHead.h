//
//		File Name �F PlayerHead.h
//		Production�F 2023/12/27
//		Author�@�@�F �Γc ����	
// 
//		�v���C���[�̊e�p�[�c����
//	
#pragma once
#include "../Player.h"
#include "../PlayeComponent/PlayerComponent.h"

class Player;

class PlayerHead final : public PlayerComponent
{
public:

	//	���S���̉���
	static const DirectX::SimpleMath::Vector3 DEATH_ACCELERATION;
	//	���̒n�ʂ̈ʒu
	static const float						  GROUND_HEAD_POSITION;
	//	�h���傫��
	static const float						  SHAKE_VOLUME;

	//	�ϐ�
private:

	//	���f��
	DirectX::Model* m_model;
	//	�o�ߎ���
	float			m_elapsedTime;
	//	�]���Ă����
	float			m_excessiveForce;

	//	�֐�
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="root">���[�g</param>
	/// <param name="paren">�e</param>
	PlayerHead(Player* root, Object* parent);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~PlayerHead();

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