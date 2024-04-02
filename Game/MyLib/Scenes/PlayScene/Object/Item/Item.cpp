//
//		File Name �F Item.cpp
//		Production�F 2023/12/1
//		Author�@�@�F �Γc ����	
//
#include "pch.h"
#include "Item.h"

//	�o�ߎ��Ԃ𑁂߂�
const float Item::INCREASE_TIMER	  = 2.5f;
//	�T�C���g������������
const float Item::LIMITS_VALUE		  = 0.01f;
//	�傫��������������l
const float Item::SCALE_SMALLER_VALUE = 0.05f;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="position">���W</param>
/// <param name="itemType">�A�C�e���̎��</param>
Item::Item(const DirectX::SimpleMath::Vector3& position, const ItemType& itemType)
	:
	Object(position),
	m_itemType(itemType),
	m_elapsedTime(0.0f),
	m_isTookItem(false), 
	m_isTookAnimation(false)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Item::~Item()
{
}

/// <summary>
/// ����������
/// </summary>
void Item::Initialize()
{
	//	�����蔻��̐ݒ������
	m_sphere.center = GetPosition();
	m_sphere.radius = 0.7f;
	//	�I�u�W�F�N�g�̃^�C�v��ݒ肷��
	SetType(Object::ObjectType::Item);

	m_itemCapsule = std::make_unique<ItemCapsule>(this);
	m_itemCapsule->Initialize();
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void Item::Update(const DX::StepTimer& timer)
{
	//	�擾���̃A�j���[�V����
	if (m_isTookAnimation)
	{
		SetScale(GetScale() - DirectX::SimpleMath::Vector3(SCALE_SMALLER_VALUE));

		//	0.0���傫���Ȃ�A��
		if (GetScale().x > 0.0f && GetScale().y > 0.0f && GetScale().z > 0.0f)	return;

		//	�A�C�e�����擾����
		m_isTookItem = true;

		return;
	}

	//	�o�ߎ��Ԃ��擾����
	m_elapsedTime = static_cast<float>(timer.GetTotalSeconds());
	//	���W���擾����
	DirectX::SimpleMath::Vector3 position = GetPosition();
	//	�ӂ�ӂ悳����
	position.y += LIMITS_VALUE * sinf(m_elapsedTime * INCREASE_TIMER);
	//	������x�܂ōs�����珉��������
	if (m_elapsedTime >= 1000.0f)	m_elapsedTime = 0.0f;
	//	���W��ݒ肷��
	SetPosition(position);
	//	�J�v�Z���̍X�V
	m_itemCapsule->Update(timer);
}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="view">�r���[�v���W�F�N�V����</param>
/// <param name="proj">�r���[</param>
void Item::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	//	�J�v�Z���̕`��
	m_itemCapsule->Render(view, proj);
}

/// <summary>
/// �I������
/// </summary>
void Item::Finalize()
{
}

/// <summary>
/// �A�C�e�����擾���ꂽ
/// </summary>
void Item::TookItem()
{
	m_isTookAnimation = true;
}

/// <summary>
/// �����蔻���ݒ肷��
/// </summary>
/// <param name="sphere">��</param>
void Item::SetSphere(const Collision::Shape::Sphere& sphere)
{
	m_sphere = sphere;
}