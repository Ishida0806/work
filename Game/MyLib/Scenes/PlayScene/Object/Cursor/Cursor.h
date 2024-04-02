#pragma once

//	�ȉ��J�[�\���Ăяo��
#include "ICursorComponent.h"
#include "ICursorFactory.h"
#include "CursorFactory.h"
#include "CursorBottom.h"
#include "CursorTop.h"

interface ICursorComponent;

class Cursor : public  ICursorComponent 
{
	//	�A�N�Z�T
public:

	// �e���擾����
	inline ICursorComponent* GetParent()				 override { return nullptr; }
	// �ʒu���擾����
	inline DirectX::SimpleMath::Vector3 GetPosition()	 override { return m_cursorPosition; }
	//	��]�p���擾����
	inline DirectX::SimpleMath::Quaternion GetRotate()   override { return m_cursorRotate; }
	// ��]�p���擾����
	inline float GetAngle()								 override { return m_cursorAngle; }
	// ���f�����擾����
	inline DirectX::Model* GetModel()					 override { return nullptr; }

	//	�ϐ�
private:
	//	�J�[�\���̍��W
	DirectX::SimpleMath::Vector3	 m_cursorPosition;
	//	�J�[�\���̉�]
	DirectX::SimpleMath::Quaternion	 m_cursorRotate;
	//	�J�[�\���̊p�x
	float m_cursorAngle;

	//	���i�N����
	std::unique_ptr<ICursorComponent> m_curorParts;

	//	�����蔻��悤	
	Collision::Shape::Segment m_mouseSegementPos;
	Collision::Shape::Triangle m_tri1;
	Collision::Shape::Triangle m_tri2;

	//	�֐�
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="position">���W</param>
	/// <param name="rotate">��]�p</param>
	/// <param name="angle">�p�x</param>
	Cursor(
		const DirectX::SimpleMath::Vector3&      position,
		const DirectX::SimpleMath::Quaternion&	 rotate,
		const float angle
	);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Cursor();

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

	//	�Q�Ƃ����p�x�Ɋ��蓖�Ă�
	void CalculateAngleRotate(const DirectX::SimpleMath::Vector3& position, float& angle);

	// �C�����i��ǉ�����
	void AddCurortPart(std::unique_ptr<ICursorComponent> turretParts);

private:

	void CreatePosCursor();

	DirectX::SimpleMath::Matrix CreateMatrixScreen2WorldPos(int screen_w,int screen_h,const DirectX::SimpleMath::Matrix& view,const DirectX::SimpleMath::Matrix& proj);
	// �O�p���ʂƂ̌�_����Ă����
	bool IntersectSegmentAndTriangle(DirectX::SimpleMath::Vector3 p, DirectX::SimpleMath::Vector3 q, Collision::Shape::Triangle tri, DirectX::SimpleMath::Vector3* s);
};

