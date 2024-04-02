//
//		File Name �F PlayerBody.cpp
//		Production�F 2023/12/27
//		Author�@�@�F �Γc ����	
// 
//		�v���C���[�̊e�p�[�c����
//	
#include "pch.h"
#include "PlayerBody.h"

#include "../PlayeComponent/PlayerPartsFactory.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="root">���[�g</param>
/// <param name="paren">�e</param>
PlayerBody::PlayerBody(Player* root, Object* parent)
	:PlayerComponent(root, parent),
	m_model(nullptr)
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayerBody::~PlayerBody()
{
}

/// <summary>
/// ����������
/// </summary>
void PlayerBody::Initialize()
{
	m_model = MyLib::ResourcesData::GetInstance()->GatModel(L"playerBody");

	//	�p�[�c�̒ǉ�
	m_playerParts.push_back(PlayerPartsFactory::CreatePlayerHead(	GetRoot(),	this));
	m_playerParts.push_back(PlayerPartsFactory::CreatePlayerLeftArm(GetRoot(),  this));
	m_playerParts.push_back(PlayerPartsFactory::CreatePlayerRightArm(GetRoot(), this));
	m_playerParts.push_back(PlayerPartsFactory::CreatePlayerLeftLeg(GetRoot(),  this));
	m_playerParts.push_back(PlayerPartsFactory::CreatePlayerRightLeg(GetRoot(), this));
	m_playerParts.push_back(PlayerPartsFactory::CreatePlayerCloak(	GetRoot(),  this));
}

/// <summary>
/// ���i���X�V����
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void PlayerBody::UpdateParts(const DX::StepTimer& timer)
{
	for (const auto& parts : m_playerParts)	parts->UpdateParts(timer);
}

/// <summary>
/// ���S�A�j���[�V����
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void PlayerBody::DeathAnimation(const DX::StepTimer& timer)
{
	//	�v���C���[���������ɓ|��
	SetRotate
	(
		DirectX::SimpleMath::Quaternion::Lerp
		(
			GetRotate(),
			DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitX, DirectX::XMConvertToRadians(90.0f)) * GetRoot()->GetRotate(),
			0.01f
		)
	);

	for (const auto& parts : m_playerParts) { parts->DeathAnimation(timer); }
}

/// <summary>
/// �����A�j���[�V����
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void PlayerBody::WinAnimation(const DX::StepTimer& timer)
{
	using namespace DirectX::SimpleMath;
	//	�o�ߎ��Ԃ𑫂�
	m_elapsedTime += static_cast<float>(timer.GetElapsedSeconds());
	//	�p�[�c�̍X�V
	for (const auto& parts : m_playerParts) { parts->WinAnimation(timer); }
	//	�̂����E�ɗh�炷
	SetPosition(Vector3(sinf(m_elapsedTime * 2.0f) * 0.01f , 0.0f, 0.0f));
}

/// <summary>
/// ���f���̕`��
/// </summary>
/// <param name="model">���f��</param>
/// <param name="world">���[���h</param>
/// <param name="view">�r���[</param>
/// <param name="proj">�v���W�F�N�V����</param>
void PlayerBody::DrawModel(DirectX::Model* model, const DirectX::SimpleMath::Matrix& world, const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	UNREFERENCED_PARAMETER(world);
	UNREFERENCED_PARAMETER(model);

	DirectX::SimpleMath::Quaternion parentRotate;

	//	���S�����H
	if (GetRoot()->IsDeathAnimation())	parentRotate = GetRotate();
	else								parentRotate = GetRoot()->GetRotate() * GetRotate();

	//	�ړ��s��
	DirectX::SimpleMath::Matrix trans = DirectX::SimpleMath::Matrix::CreateTranslation(GetRoot()->GetPosition() + GetPosition());
	//	��]�s��
	DirectX::SimpleMath::Matrix rotate = DirectX::SimpleMath::Matrix::CreateFromQuaternion(parentRotate);
	//	�g��s��
	DirectX::SimpleMath::Matrix scale = DirectX::SimpleMath::Matrix::CreateScale(GetRoot()->GetScale());
	//	���[���h
	DirectX::SimpleMath::Matrix wrd = scale * rotate * trans;
	//	���f���̕`��
	PlayerComponent::DrawModel(m_model, wrd, view, proj);

	for (const auto& parts : m_playerParts)	parts->DrawModel(nullptr, wrd, view, proj);
}