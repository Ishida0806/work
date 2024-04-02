//
//		File Name �F RecoveryItem.cpp
//		Production�F 2023/12/1
//		Author�@�@�F �Γc ����	
//
#include "pch.h"
#include "RecoveryItem.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="position">���W</param>
/// <param name="itemType">�A�C�e���̎��</param>
RecoveryItem::RecoveryItem(const DirectX::SimpleMath::Vector3& position, const ItemType& itemType)
	:Item(position, itemType),
	m_model(nullptr)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
RecoveryItem::~RecoveryItem()
{
}

/// <summary>
/// ����������
/// </summary>
void RecoveryItem::Initialize()
{
	m_model = MyLib::ResourcesData::GetInstance()->GatModel(L"recovery");

	Item::Initialize();
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void RecoveryItem::Update(const DX::StepTimer& timer)
{
	//	���N���X���X�V����
	Item::Update(timer);
}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="view">�r���[</param>
/// <param name="proj">�v���W�F�N�V����</param>
void RecoveryItem::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	//	�����_���Ŋ֐��I�u�W�F�N�g��������
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
	//	�A�C�e���̕`��
	Item::Render(view, proj);
	//	�X�N���[��
	MyLib::ScreenResources* screen	  = MyLib::ScreenResources::GetInstance();
	//	�X�P�[�����O�s����쐬����
	DirectX::SimpleMath::Matrix scale = DirectX::SimpleMath::Matrix::CreateScale(GetScale());
	//	�ړ��s����쐬	
	DirectX::SimpleMath::Matrix trans = DirectX::SimpleMath::Matrix::CreateTranslation(GetPosition());

	//	�ړ��s��
	DirectX::SimpleMath::Matrix world = scale * trans;
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
void RecoveryItem::Finalize()
{
	Item::Finalize();
}
