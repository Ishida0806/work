//
//		File Name �F CursorBottom.h
//		Production�F 2023/7/02
//		Author�@�@�F �Γc ����
//
#pragma once
#include "ICursorComponent.h"

interface ICursorComponent;

class CursorBottom : public ICursorComponent
{
public:

	static const float							FRICTION_SCALE;
	static const float							CURSOR_SCALE;
	static const DirectX::SimpleMath::Vector3	BASE_SCALE;

private:
	// �e
	ICursorComponent*							   m_parent;
	//	���W
	DirectX::SimpleMath::Vector3				   m_cursorBottomPosition;
	//�傫��
	DirectX::SimpleMath::Vector3				   m_cursorBottomScale;
	//	��]�p
	DirectX::SimpleMath::Quaternion				   m_cursorBottomRotate;
	//	�p�x
	float										   m_cursorBottomAngle;
	//	����
	float										   m_second;
	//	���f��
	DirectX::Model*								   m_cursorBottomModel;
	//	�J�[�\���̃p�[�c
	std::vector<std::unique_ptr<ICursorComponent>> m_curorParts;


public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="parent">�e</param>
	/// <param name="position">���W</param>
	/// <param name="rotate">��]�p</param>
	CursorBottom(
		ICursorComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& rotate
	);
	~CursorBottom();

	// �e���擾����
	ICursorComponent* GetParent()	override { return m_parent; }
	// �ʒu���擾����
	DirectX::SimpleMath::Vector3	GetPosition() override { return m_cursorBottomPosition; }
	//	��]�p���擾����
	DirectX::SimpleMath::Quaternion GetRotate()   override { return m_cursorBottomRotate; }
	// ��]�p���擾����
	float GetAngle()  override { return m_cursorBottomAngle;}
	// ���f�����擾����
	DirectX::Model* GetModel() override { return m_cursorBottomModel; }
public:
	//	����������
	void Initialize() override;
	//	�X�V����
	void Update(const DX::StepTimer& timer) override;
	//	�`�揈��
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj) override;
	//	�I������	
	void Finalize() override;
	// �C�����i��ǉ�����
	void AddCurortPart(std::unique_ptr<ICursorComponent> turretParts);
};
