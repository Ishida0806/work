//
//		File Name �F PlayerLeftLeg.cpp
//		Production�F 2023/12/27
//		Author�@�@�F �Γc ����	
// 
//		�v���C���[�̊e�p�[�c����
//	
#include "pch.h"
#include "PlayerLeftLeg.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="root">���[�g</param>
/// <param name="paren">�e</param>
PlayerLeftLeg::PlayerLeftLeg(Player* root, Object* parent)
	:PlayerComponent(root, parent),
	m_model(nullptr),
	m_elapsedTime(0.0f)
{
	
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayerLeftLeg::~PlayerLeftLeg()
{
}

/// <summary>
/// ����������
/// </summary>
void PlayerLeftLeg::Initialize()
{
	m_model = MyLib::ResourcesData::GetInstance()->GatModel(L"playerLeftLeg");
}

/// <summary>
/// ���i���X�V����
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void PlayerLeftLeg::UpdateParts(const DX::StepTimer& timer)
{
	UNREFERENCED_PARAMETER(timer);

	//	�o�ߎ��Ԃ𑫂�
	if (GetRoot()->IsWalk())
	{
		m_elapsedTime -= static_cast<float>(timer.GetElapsedSeconds());
		//	�����㉺�ɗh�炷
		SetPosition(GetPosition() + DirectX::SimpleMath::Vector3(0.0f, 0.0f, sinf(m_elapsedTime * 5.0f) * 0.08f));
	}
	else
	{
		m_elapsedTime = 0.0f;
		SetPosition(DirectX::SimpleMath::Vector3::Lerp(GetPosition(), DirectX::SimpleMath::Vector3::Zero, 0.2f));
	}

	SetPosition(DirectX::SimpleMath::Vector3::Lerp(GetPosition(), DirectX::SimpleMath::Vector3::Zero, 0.1f));
}

/// <summary>
/// ���S�A�j���[�V����
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void PlayerLeftLeg::DeathAnimation(const DX::StepTimer& timer)
{
	UNREFERENCED_PARAMETER(timer);


}

/// <summary>
/// �����A�j���[�V����
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void PlayerLeftLeg::WinAnimation(const DX::StepTimer& timer)
{
	using namespace DirectX::SimpleMath;
	//	�o�ߎ��Ԃ𑫂�
	m_elapsedTime += static_cast<float>(timer.GetElapsedSeconds());
	//	�r��������������
	SetPosition(Vector3(0.0f, sinf(m_elapsedTime * 3.0f) * 0.05f, 0.0f));
}

/// <summary>
/// ���f���̕`��
/// </summary>
/// <param name="model">���f��</param>
/// <param name="world">���[���h</param>
/// <param name="view">�r���[</param>
/// <param name="proj">�v���W�F�N�V����</param>
void PlayerLeftLeg::DrawModel(DirectX::Model* model, const DirectX::SimpleMath::Matrix& world, const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	UNREFERENCED_PARAMETER(world);
	UNREFERENCED_PARAMETER(model);


	DirectX::SimpleMath::Quaternion parentRotate;

	//	���S�����H
	if (GetRoot()->IsDeathAnimation())	parentRotate = GetParent()->GetRotate() * GetRotate();
	else								parentRotate = GetRoot()->GetRotate() * GetRotate();

	//	�ړ��s��
	DirectX::SimpleMath::Matrix trans = DirectX::SimpleMath::Matrix::CreateTranslation(GetRoot()->GetPosition() + GetPosition());
	//	��]�s��
	DirectX::SimpleMath::Matrix rotate = DirectX::SimpleMath::Matrix::CreateFromQuaternion(parentRotate);
	//	�g��s��
	DirectX::SimpleMath::Matrix scale = DirectX::SimpleMath::Matrix::CreateScale(GetRoot()->GetScale());
	//	���[���h
	DirectX::SimpleMath::Matrix wrd = scale * rotate * trans;

	PlayerComponent::DrawModel(m_model, wrd, view, proj);
}