//
//		File Name �F ReflectItem.cpp
//		Production�F 2023/12/1
//		Author�@�@�F �Γc ����	
//
#include "pch.h"
#include "ReflectItem.h"


//	��������p�x
const float ReflectItem::INCREASE_ANGLE = 2.0f;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="position">���W</param>
/// <param name="itemType">�A�C�e���̎��</param>
ReflectItem::ReflectItem(const DirectX::SimpleMath::Vector3& position, const ItemType& itemType)
	:Item(position, itemType),
	m_model(nullptr)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ReflectItem::~ReflectItem()
{
}

/// <summary>
/// ����������
/// </summary>
void ReflectItem::Initialize()
{
	m_model = MyLib::ResourcesData::GetInstance()->GatModel(L"bat");

	Item::Initialize();
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void ReflectItem::Update(const DX::StepTimer& timer)
{
	//	�A�C�e�����擾����
	//if (IsTookItem())	return;

	SetAngle(GetAngle() + DirectX::XMConvertToRadians(INCREASE_ANGLE));

	m_reflectRotate = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, GetAngle());
	m_reflectRotate = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitZ, GetAngle());


	//	���N���X���X�V����
	Item::Update(timer);
}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="view">�r���[</param>
/// <param name="proj">�v���W�F�N�V����</param>
void ReflectItem::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	m_model->UpdateEffects
	(
		[&](DirectX::IEffect* effect)
		{
			auto basicEffect = dynamic_cast<DirectX::BasicEffect*>(effect);
			//	�L���X�g�ł������H
			if (basicEffect)
			{
				//	�摜����Ȃ�
				basicEffect->SetTexture(nullptr);
			}
		}
	);

	Item::Render(view, proj);

	MyLib::ScreenResources* screen	  = MyLib::ScreenResources::GetInstance();
	//	�X�P�[�����O�s����쐬����
	DirectX::SimpleMath::Matrix scale = DirectX::SimpleMath::Matrix::CreateScale(GetScale());
	//	�ړ��s����쐬	
	DirectX::SimpleMath::Matrix trans = DirectX::SimpleMath::Matrix::CreateTranslation(GetPosition());
	//	��]�s����쐬
	DirectX::SimpleMath::Matrix roate = DirectX::SimpleMath::Matrix::CreateFromQuaternion(m_reflectRotate);
	//	���[���h�s����쐬
	DirectX::SimpleMath::Matrix world = scale * roate * trans;
	//	���f���`�揈��
	m_model->Draw
		(
			screen->GetDeviceContext(),
			*screen->GetCommonState(),
			world,
			view,
			proj
		);
}

/// <summary>
/// �I������
/// </summary>
void ReflectItem::Finalize()
{
	Item::Finalize();
}
