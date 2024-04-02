//
//		File Name �F PlayerRightArm.cpp
//		Production�F 2023/12/27
//		Author�@�@�F �Γc ����	
// 
//		�v���C���[�̊e�p�[�c����
//	
#include "pch.h"
#include "PlayerRightArm.h"

//	�����ۂ̗h���
const float						   PlayerRightArm::WALK_SHAKE		  = 0.01f;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="root">���[�g</param>
/// <param name="paren">�e</param>
PlayerRightArm::PlayerRightArm(Player* root, Object* parent)
	:PlayerComponent(root, parent),
	m_elapsedTime(0.0f),
	m_model(nullptr)
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayerRightArm::~PlayerRightArm()
{
}

/// <summary>
/// ����������
/// </summary>
void PlayerRightArm::Initialize()
{
	m_model = MyLib::ResourcesData::GetInstance()->GatModel(L"playerRightArm");
}

/// <summary>
/// ���i���X�V����
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void PlayerRightArm::UpdateParts(const DX::StepTimer& timer)
{
	UNREFERENCED_PARAMETER(timer);
}

/// <summary>
/// ���S�A�j���[�V����
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void PlayerRightArm::DeathAnimation(const DX::StepTimer& timer)
{
	UNREFERENCED_PARAMETER(timer);
	//	���̈ʒu�̖߂�
	SetPosition(DirectX::SimpleMath::Vector3::Lerp(GetPosition(), DirectX::SimpleMath::Vector3::Zero, 0.1f));
}

/// <summary>
/// �����A�j���[�V����
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void PlayerRightArm::WinAnimation(const DX::StepTimer& timer)
{
	using namespace DirectX::SimpleMath;

	m_elapsedTime += static_cast<float>(timer.GetElapsedSeconds());

	SetRotate(Quaternion(GetRotate() * Quaternion::CreateFromAxisAngle(Vector3::UnitY, DirectX::XMConvertToRadians(sinf(m_elapsedTime * 5.0f) * 3.f))));
	SetRotate(Quaternion(GetRotate() * Quaternion::CreateFromAxisAngle(Vector3::UnitZ, DirectX::XMConvertToRadians(sinf(m_elapsedTime * 5.0f) * 3.f))));

	SetPosition(Vector3(0.0f, 1.7f, 0.0f));
}

/// <summary>
/// ���f���̕`��
/// </summary>
/// <param name="model">���f��</param>
/// <param name="world">���[���h</param>
/// <param name="view">�r���[</param>
/// <param name="proj">�v���W�F�N�V����</param>
void PlayerRightArm::DrawModel(DirectX::Model* model, const DirectX::SimpleMath::Matrix& world, const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	UNREFERENCED_PARAMETER(world);
	UNREFERENCED_PARAMETER(model);

	DirectX::SimpleMath::Quaternion parentRotate;
	//	���S�����H
	if (GetRoot()->IsDeathAnimation()) { parentRotate = GetParent()->GetRotate() * GetRotate(); } else { parentRotate = GetRoot()->GetRotate() * GetRotate(); }
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