//
//		File Name �F PowerUPItem.cpp
//		Production�F 2023/12/1
//		Author�@�@�F �Γc ����	
//
#include "pch.h"
#include "PowerUPItem.h"

//	��������p�x
const float PowerUPItem::INCREASE_ANGLE = 2.0f;
//	�h�炷�͈͂̐���
const float PowerUPItem::SHAKE_RANGE	= 0.3f;



/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="position">���W</param>
/// <param name="itemType">�A�C�e���̎��</param>
PowerUPItem::PowerUPItem(const DirectX::SimpleMath::Vector3& position, const ItemType& itemType)
	:Item(position, itemType),
	m_model(nullptr),
	m_elapsedTime(0.0f)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PowerUPItem::~PowerUPItem()
{
}

/// <summary>
/// ����������
/// </summary>
void PowerUPItem::Initialize()
{
	m_model = MyLib::ResourcesData::GetInstance()->GatModel(L"armPower");

	Item::Initialize();
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void PowerUPItem::Update(const DX::StepTimer& timer)
{
	//	���N���X���X�V����
	Item::Update(timer);

	//	�o�ߎ��Ԃ��擾����
	m_elapsedTime = static_cast<float>(timer.GetTotalSeconds());

	m_powerUPRotate = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, SHAKE_RANGE * sinf(m_elapsedTime));

	//	������x�܂ōs�����珉��������
	if (m_elapsedTime >= 1000.0f)	m_elapsedTime = 0.0f;
}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="view">�r���[</param>
/// <param name="proj">�v���W�F�N�V����</param>
void PowerUPItem::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
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

	MyLib::ScreenResources*		screen = MyLib::ScreenResources::GetInstance();
	//	�X�P�[�����O�s����쐬����
	DirectX::SimpleMath::Matrix scale  = DirectX::SimpleMath::Matrix::CreateScale(GetScale());
	//	�ړ��s����쐬	
	DirectX::SimpleMath::Matrix trans  = DirectX::SimpleMath::Matrix::CreateTranslation(GetPosition());
	//	��]�s��
	DirectX::SimpleMath::Matrix rotate = DirectX::SimpleMath::Matrix::CreateFromQuaternion(m_powerUPRotate);
	//	���[���h�s����쐬
	DirectX::SimpleMath::Matrix world  = scale * rotate * trans;
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
void PowerUPItem::Finalize()
{
	Item::Finalize();
}