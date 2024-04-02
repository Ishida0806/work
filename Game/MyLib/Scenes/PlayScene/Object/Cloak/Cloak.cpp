//
//		File Name �F Cloak.cpp
//		Production�F 2023/12/27
//		Author�@�@�F �Γc ����
// 
//		�}���g	
//	
#include "pch.h"
#include "Cloak.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="root">���[�g</param>
/// <param name="parent">�e</param>
Cloak::Cloak(Player* root, Object* parent)
	:PlayerComponent(root, parent),
	m_model(nullptr),
	m_elapsedTime(0.0f)
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Cloak::~Cloak()
{
}

/// <summary>
/// ����������
/// </summary>
void Cloak::Initialize()
{
	m_model = MyLib::ResourcesData::GetInstance()->GatModel(L"cloak");

	m_model->UpdateEffects
	(
		[&](DirectX::IEffect* effect)
		{
			//	�x�[�V�b�N�G�t�F�N�g
			auto basicEffect = dynamic_cast<DirectX::BasicEffect*>(effect);
			//	�|�C���^�͑��݂��邩�H
			if (basicEffect)
			{
				//	����
				basicEffect->SetAmbientLightColor(DirectX::Colors::White);
			}
		}
	);
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void Cloak::UpdateParts(const DX::StepTimer& timer)
{
	using namespace DirectX::SimpleMath;

	m_elapsedTime += static_cast<float>(timer.GetElapsedSeconds());

	//if (GetRoot()->IsAttack())
	//{
	//	DirectX::SimpleMath::Quaternion lastRotate = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(Vector3::UnitX, 0.3f * sinf(m_elapsedTime));

	//	SetRotate(Quaternion::Lerp(GetRotate(), lastRotate, 0.03f));
	//}
	//else
	//{
	//	SetRotate(DirectX::SimpleMath::Quaternion::Lerp(GetRotate(), DirectX::SimpleMath::Quaternion::Identity, 0.1f));

	//	//m_elapsedTime = 0.0f;
	//}

	if (GetRoot()->IsWalk())
	{
		DirectX::SimpleMath::Vector3 position = GetPosition();

		position.y += sinf(m_elapsedTime);

		SetVelocity(position);
	}
	else
	{
		m_elapsedTime = 0.0f;
	}
}

/// <summary>
/// ���S�A�j���[�V����
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void Cloak::DeathAnimation(const DX::StepTimer& timer)
{
	UNREFERENCED_PARAMETER(timer);
}


/// <summary>
/// ���f���̕`��
/// </summary>
/// <param name="model">���f��</param>
/// <param name="world">���[���h</param>
/// <param name="view">�r���[</param>
/// <param name="proj">�v���W�F�N�V����</param>
void Cloak::DrawModel(DirectX::Model* model, const DirectX::SimpleMath::Matrix& world, const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	UNREFERENCED_PARAMETER(world);
	UNREFERENCED_PARAMETER(model);

	DirectX::SimpleMath::Quaternion parentRotate;

	//	���S�����H
	if (GetRoot()->IsDeathAnimation()) { parentRotate = GetParent()->GetRotate() * GetRotate(); } else { parentRotate = GetRoot()->GetRotate() * GetRotate(); }
	//	�ړ��s��
	DirectX::SimpleMath::Matrix trans = DirectX::SimpleMath::Matrix::CreateTranslation(GetRoot()->GetPosition() + DirectX::SimpleMath::Vector3(0.0f, 0.44f, 0.1f));
	//	��]�s��
	DirectX::SimpleMath::Matrix rotate = DirectX::SimpleMath::Matrix::CreateFromQuaternion(parentRotate);
	//	�g��s��
	DirectX::SimpleMath::Matrix scale = DirectX::SimpleMath::Matrix::CreateScale(1.5f);
	//	���[���h
	DirectX::SimpleMath::Matrix wrd = scale * rotate * trans;
	//	���f���̕`��
	PlayerComponent::DrawModel(m_model, wrd, view, proj);
}
