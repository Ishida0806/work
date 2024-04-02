//
//		File Name �F RecoveryItem.h
//		Production�F 2023/12/1
//		Author�@�@�F �Γc ����	
//
#pragma once
#include "../Item/Item.h"

class Item;

class RecoveryItem : public Item
{
	//	�ϐ�
private:

	//	���f��
	DirectX::Model* m_model;

	//	�֐�
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="position">���W</param>
	/// <param name="itemType">�A�C�e���̎��</param>
	RecoveryItem(const DirectX::SimpleMath::Vector3& position, const ItemType& itemType = ItemType::None);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~RecoveryItem();

	/// <summary>
	/// ����������
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="timer">�^�C�}�[</param>
	void Update(const DX::StepTimer& timer) override;

	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name="view">�r���[�v���W�F�N�V����</param>
	/// <param name="proj">�r���[</param>
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj) override;

	/// <summary>
	/// �I������
	/// </summary>
	void Finalize() override;
};