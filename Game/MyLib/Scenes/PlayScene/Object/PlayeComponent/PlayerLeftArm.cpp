//
//		File Name �F PlayerLeftArm.cpp
//		Production�F 2023/12/27
//		Author�@�@�F �Γc ����	
// 
//		�v���C���[�̊e�p�[�c����
//	
#include "pch.h"
#include "PlayerLeftArm.h"

//	���S���̉���
const DirectX::SimpleMath::Vector3 PlayerLeftArm::DEATH_ACCELERATION = DirectX::SimpleMath::Vector3(-0.35f, -0.025f, -0.020f);
//	�����ۂ̗h���
const float						   PlayerLeftArm::CORRECTION_SPEED	 = 0.0125f;
//	���Ԃ̉����x
const float						   PlayerLeftArm::ACCELERATION_TIMER = 5.0f;
//	���W��߂����x
const float						   PlayerLeftArm::RETURN_SPEED		 = 0.1f;


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="root">���[�g</param>
/// <param name="paren">�e</param>
PlayerLeftArm::PlayerLeftArm(Player* root, Object* parent)
	:PlayerComponent(root, parent),
	m_model(nullptr),
	m_elapsedTime(0.0f)
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayerLeftArm::~PlayerLeftArm()
{
}

/// <summary>
/// ����������
/// </summary>
void PlayerLeftArm::Initialize()
{
	m_model = MyLib::ResourcesData::GetInstance()->GatModel(L"playerLeftArm");
}

/// <summary>
/// ���i���X�V����
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void PlayerLeftArm::UpdateParts(const DX::StepTimer& timer)
{
	UNREFERENCED_PARAMETER(timer);

	using namespace DirectX::SimpleMath;
	//	�o�ߎ��Ԃ𑫂�
	if (GetRoot()->IsWalk())
	{
		m_elapsedTime += static_cast<float>(timer.GetElapsedSeconds());
		//	�r���㉺�ɗh�炷
		SetPosition(GetPosition() + DirectX::SimpleMath::Vector3(0.0f, 0.0f, sinf(m_elapsedTime * ACCELERATION_TIMER) * CORRECTION_SPEED));
	}
	else
	{
		m_elapsedTime = 0.0f;
		SetPosition(DirectX::SimpleMath::Vector3::Lerp(GetPosition(), DirectX::SimpleMath::Vector3::Zero, RETURN_SPEED));
	}
	//	���̈ʒu�̖߂�
	SetPosition(DirectX::SimpleMath::Vector3::Lerp(GetPosition(), DirectX::SimpleMath::Vector3::Zero, RETURN_SPEED));
}

/// <summary>
/// ���S�A�j���[�V����
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void PlayerLeftArm::DeathAnimation(const DX::StepTimer& timer)
{
	UNREFERENCED_PARAMETER(timer);
}

/// <summary>
/// �����A�j���[�V����
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void PlayerLeftArm::WinAnimation(const DX::StepTimer& timer)
{
	using namespace DirectX::SimpleMath;

	//if (m_elapsedTime == 0.0f)
	//{
	//	//	������ꎞ������
	//	SetRotate(DirectX::SimpleMath::Quaternion::Identity);
	//}

	m_elapsedTime += static_cast<float>(timer.GetElapsedSeconds());

	SetRotate(Quaternion(GetRotate() * Quaternion::CreateFromAxisAngle(Vector3::UnitY, DirectX::XMConvertToRadians(-sinf(m_elapsedTime * 5.0f) * 3.f))));
	SetRotate(Quaternion(GetRotate() * Quaternion::CreateFromAxisAngle(Vector3::UnitZ, DirectX::XMConvertToRadians(-sinf(m_elapsedTime * 5.0f) * 3.f))));

	SetPosition(Vector3(0.0f, 1.7f, 0.0f));
}

/// <summary>
/// ���f���̕`��
/// </summary>
/// <param name="model">���f��</param>
/// <param name="world">���[���h</param>
/// <param name="view">�r���[</param>
/// <param name="proj">�v���W�F�N�V����</param>
void PlayerLeftArm::DrawModel(DirectX::Model* model, const DirectX::SimpleMath::Matrix& world, const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
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