//
//		File Name �F ItemCapsule.cpp
//		Production�F 2023/12/06
//		Author�@�@�F �Γc ����	
//
#include "pch.h"
#include "ItemCapsule.h"
#include "ItemCapsuleFactory.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="parent">�e</param>
ItemCapsule::ItemCapsule(Object* parent)
	:m_parent(parent)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ItemCapsule::~ItemCapsule()
{
}

/// <summary>
/// ����������
/// </summary>
void ItemCapsule::Initialize()
{
	//	�p�[�c��ǉ�
	m_parts.push_back(ItemCapsuleFactory::CreateItemCapsuleBottom(m_parent));
	m_parts.push_back(ItemCapsuleFactory::CreateItemCapsuleTop(m_parent));
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void ItemCapsule::Update(const DX::StepTimer& timer)
{
	for (const auto& part : m_parts) part->Update(timer);
}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="view">�r���[</param>
/// <param name="proj">�v���W�F�N�V����</param>
void ItemCapsule::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	for (const auto& part : m_parts) part->Render(view, proj);
}

/// <summary>
/// �I������
/// </summary>
void ItemCapsule::Finalize()
{
	for (const auto& part : m_parts) part->Finalize();
}
