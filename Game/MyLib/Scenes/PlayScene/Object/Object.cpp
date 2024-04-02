//
//		File Name �F Object.cpp
//		Production�F 2023/6/19
//		Author�@�@�F �Γc ����	
// 
//		�e�I�u�W�F�N�g�̊��N���X
//	
#include "pch.h"
#include "Object.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Object::Object()
	:m_scale(1.0f),
	m_angle(0.0f)
{
}

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="position">���W</param>
Object::Object(const DirectX::SimpleMath::Vector3& position)
	:m_position(position),
	m_scale(1.0f),
	m_angle(0.0f)
{
}

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="position">���W</param>
/// <param name="rotate">��]�p</param>
Object::Object(const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion rotate)
	:m_position(position),
	m_rotate(rotate),
	m_scale(1.0f),
	m_angle(0.0f)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Object::~Object()
{
}

/// <summary>
/// ����������
/// </summary>
void Object::Initialize()
{
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void Object::Update(const DX::StepTimer& timer)
{
	timer;
}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="view">�r���[</param>
/// <param name="proj">�v���W�F�N�V����</param>
void Object::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	view;
	proj;
}

/// <summary>
/// �I������
/// </summary>
void Object::Finalize()
{

}

/// <summary>
/// �ʏ�̓����蔻����擾����
/// </summary>
/// <param name="type">�����蔻��̎��</param>
/// <param name="size">�傫��</param>
/// <returns>�|�C���^�[<</returns>
Collision::CollisionBehavior* Object::GetColision(ColisionType type, unsigned int& size) const
{
	//	�T�C�Y��Ԃ�
	size = static_cast<unsigned int>(m_shapeColision.size());
	//	�|�C���^�[��Ԃ�
	return m_shapeColision.at(type);
}

/// <summary>
/// ���W��ݒ肷��
/// </summary>
/// <param name="position"></param>
void Object::SetPosition(const DirectX::SimpleMath::Vector3& position)
{
	m_position = position;
}

/// <summary>
/// �ړ��ʂ�ݒ肷��
/// </summary>
/// <param name="velocity">�ړ���</param>
void Object::SetVelocity(const DirectX::SimpleMath::Vector3& velocity)
{
	m_position += velocity;
}

/// <summary>
/// �傫����ݒ肷��
/// </summary>
/// <param name="scale">�傫��</param>
void Object::SetScale(const DirectX::SimpleMath::Vector3& scale)
{
	m_scale = scale;
}

/// <summary>
/// ��]�p��ݒ肷��
/// </summary>
/// <param name="rotate"></param>
void Object::SetRotate(const DirectX::SimpleMath::Quaternion& rotate)
{
	m_rotate = rotate;
}

/// <summary>
/// �p�x��ݒ肷��
/// </summary>
/// <param name="angle"></param>
void Object::SetAngle(const float& angle)
{
	m_angle = angle;
}

/// <summary>
/// ID��ݒ肷��
/// </summary>
/// <param name="id"></param>
void Object::SetType(const Object::ObjectType& obj)
{
	m_objType = obj;
}
