//
//		File Name �F ItemCapsule.h
//		Production�F 2023/12/06
//		Author�@�@�F �Γc ����	
//
#pragma once 
#include "../Object.h"
#include "IItemCapsuleComponent.h"

class ItemCapsule : public Object , public IItemCapsuleComponent
{
	//	�ϐ�
private:
	//	�p�[�c�B
	std::vector<std::unique_ptr<Object>>	m_parts;
	//	�e
	Object*									m_parent;

	//	�֐�
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="parent">�e</param>
	ItemCapsule(Object* parent);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~ItemCapsule();

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