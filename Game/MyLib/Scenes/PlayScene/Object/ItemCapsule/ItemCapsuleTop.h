//
//		File Name �F ItemCapsuleTop.h
//		Production�F 2023/12/06
//		Author�@�@�F �Γc ����	
//
#pragma once 
#include "../Object.h"
#include "IItemCapsuleComponent.h"

class ItemCapsuleTop : public Object, public IItemCapsuleComponent
{
	//	�ϐ�
private:

	//	�e
	Object*			m_parent;
	//	���f��
	DirectX::Model* m_model;

	//	�֐�
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="Object">�e</param>
	ItemCapsuleTop(Object* parent);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~ItemCapsuleTop();

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
	/// <param name="view">�r���[</param>
	/// <param name="proj">�v���W�F�N�V����</param>
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj) override;

	/// <summary>
	/// �I������
	/// </summary>
	void Finalize() override;
};