//
//		File Name �F Cloak.h
//		Production�F 2023/12/27
//		Author�@�@�F �Γc ����	
//	
#pragma once
#include "../PlayeComponent/PlayerComponent.h"

class Cloak : public PlayerComponent
{
	//	�ϐ�
private:

	//	���f��
	DirectX::Model*					m_model;
	//	�o�ߎ���
	float							m_elapsedTime;

	//	�֐�
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="root">���[�g</param>
	/// <param name="parent">�e</param>
	Cloak(Player* root, Object* parent);
	
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Cloak();

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
	/// ���f���̕`��
	/// </summary>
	/// <param name="model">���f��</param>
	/// <param name="world">���[���h</param>
	/// <param name="view">�r���[</param>
	/// <param name="proj">�v���W�F�N�V����</param>
	void DrawModel(DirectX::Model* model, const DirectX::SimpleMath::Matrix& world, const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj) override;
};
