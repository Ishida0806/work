//
//		File Name �F ItemCapsuleTop.cpp
//		Production�F 2023/12/06
//		Author�@�@�F �Γc ����	
//
#include "pch.h"
#include "ItemCapsuleTop.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="Object">�e</param>
ItemCapsuleTop::ItemCapsuleTop(Object* parent)
	:m_parent(parent),
	m_model(nullptr)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ItemCapsuleTop::~ItemCapsuleTop()
{
}

/// <summary>
/// ����������
/// </summary>
void ItemCapsuleTop::Initialize()
{
	m_model = MyLib::ResourcesData::GetInstance()->GatModel(L"capsuleTop");
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void ItemCapsuleTop::Update(const DX::StepTimer& timer)
{
	UNREFERENCED_PARAMETER(timer);
}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="view">�r���[</param>
/// <param name="proj">�v���W�F�N�V����</param>
void ItemCapsuleTop::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	MyLib::ScreenResources* scren = MyLib::ScreenResources::GetInstance();
	//	�X�P�[�����O�s����쐬����
	DirectX::SimpleMath::Matrix scale = DirectX::SimpleMath::Matrix::CreateScale(m_parent->GetScale());
	//	�ړ��s����쐬	
	DirectX::SimpleMath::Matrix trans = DirectX::SimpleMath::Matrix::CreateTranslation(m_parent->GetPosition());
	//	��]�s����쐬
	DirectX::SimpleMath::Matrix roate = DirectX::SimpleMath::Matrix::CreateFromQuaternion(m_parent->GetRotate());
	//	���[���h�s����쐬
	DirectX::SimpleMath::Matrix world = scale * roate * trans;

	//	�`����s��
	m_model->Draw
	(
		scren->GetDeviceContext(),
		*scren->GetCommonState(),
		world,
		view,
		proj
	);
}

/// <summary>
/// �I������
/// </summary>
void ItemCapsuleTop::Finalize()
{
}
