//
//		File Name �F CursorTop.h
//		Production�F 2023/7/02
//		Author�@�@�F �Γc ����
//
#pragma once
#include "ICursorComponent.h"

interface ICursorComponent;

class CursorTop final : public ICursorComponent
{
	//	�ϐ�
private:
	// �e
	ICursorComponent* m_parent;
	//	�J�[�\���㕔�̍��W
	DirectX::SimpleMath::Vector3				   m_cursorTopPosition;
	//	�J�[�\���㕔�̉�]
	DirectX::SimpleMath::Quaternion				   m_cursorTopRotate;
	float										   m_cursorTopAngle;
	//	�J�[�\���㕔�̃��f��
	DirectX::Model*								   m_cursorTopModel;
	//	�J�[�\���̃p�[�c
	std::vector<std::unique_ptr<ICursorComponent>> m_curorParts;
	//	�o�ߎ���
	float m_second;

	//	�֐�
public:
	CursorTop(ICursorComponent* parent, const DirectX::SimpleMath::Vector3& position, const float& angle);
	~CursorTop();

	//	�A�N�Z�T
public:

	// �e���擾����
	inline ICursorComponent* GetParent() override { return m_parent; }
	// �ʒu���擾����
	inline DirectX::SimpleMath::Vector3 GetPosition()  override { return m_cursorTopPosition; }
	//	��]�p���擾����
	DirectX::SimpleMath::Quaternion GetRotate()   override { return m_cursorTopRotate; }
	// ��]�p���擾����
	inline float GetAngle()   override { return m_cursorTopAngle; }
	// ���f�����擾����
	inline DirectX::Model* GetModel()  override { return m_cursorTopModel; }
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
