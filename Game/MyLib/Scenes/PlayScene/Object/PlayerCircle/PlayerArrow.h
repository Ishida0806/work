//
//		File Name �F PlayerArrow.h
//		Production�F 2023/11/03
//		Author�@�@�F �Γc ����	
//	
#pragma once

#include "Game/MyLib/Scenes/PlayScene/Object/Object.h"

class Object;

class PlayerArrow : public Object
{
	//	�萔
public:

	//	���̈ړ����x
	static const float MOVE_ARROW_SPEED;
	//	���̉�]�p��Z
	static const float ARROW_ROTATE_Z;


	//	�ϐ�
private:

	//	��󃂃f��
	DirectX::Model*									 m_arrowModel;
	//	�e
	Object*											 m_parent;
	//	�~�̊p�x
	float											 m_circleAngle;
	//	���̊p�x
	float											 m_arrowAngle;
	//	�e���W
	DirectX::SimpleMath::Vector3					 m_position;
	//	�J�[�\���̍��W
	DirectX::SimpleMath::Vector3*					 m_cursolPosition;
	//	���̍��W
	DirectX::SimpleMath::Vector3					 m_arrowPosition;
	//	�J�[�\���̉�]�p
	DirectX::SimpleMath::Quaternion*				 m_cursolRotate;

	//	�֐�
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="parent">�e</param>
	/// <param name="arrowModel">��󃂃f��</param>
	/// <param name="cursolPosition">�J�[�\���̍��W</param>
	/// <param name="cursolRotate">�J�[�\���̉�]�p</param>
	PlayerArrow(
		Object* parent,
		DirectX::Model* arrowModel, 
		DirectX::SimpleMath::Vector3* cursolPosition,
		DirectX::SimpleMath::Quaternion* cursolRotate
	);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~PlayerArrow();

	/// <summary>
	/// ����������
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update(const DX::StepTimer& timer) override;
	
	/// <summary>
	/// �`�悷��
	/// </summary>
	/// <param name="view">�r���[</param>
	/// <param name="proj">�v���W�F�N�V����</param>
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj) override;

	/// <summary>
	/// �I������
	/// </summary>
	void Finalize() override;
};