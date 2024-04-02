//
//		File Name �F PlayerHead.cpp
//		Production�F 2023/12/27
//		Author�@�@�F �Γc ����	
// 
//		�v���C���[�̊e�p�[�c����
//	
#include "pch.h"
#include "PlayerHead.h"


//	���S���̉���
const DirectX::SimpleMath::Vector3 PlayerHead::DEATH_ACCELERATION		= DirectX::SimpleMath::Vector3(0.0f, -0.12f, 0.73f);
//	���̒n�ʂ̈ʒu
const float						   PlayerHead::GROUND_HEAD_POSITION		= -1.2f;
//	�h���傫��
const float						   PlayerHead::SHAKE_VOLUME				=  0.01f;


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="root">���[�g</param>
/// <param name="paren">�e</param>
PlayerHead::PlayerHead(Player* root, Object* parent)
	:PlayerComponent(root, parent),
	m_model(nullptr),
	m_elapsedTime(0.0f),
	m_excessiveForce(DEATH_ACCELERATION.z)
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayerHead::~PlayerHead()
{
}

/// <summary>
/// ����������
/// </summary>
void PlayerHead::Initialize()
{
	m_model = MyLib::ResourcesData::GetInstance()->GatModel(L"playerHead");
}

/// <summary>
/// ���i���X�V����
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void PlayerHead::UpdateParts(const DX::StepTimer& timer)
{
	UNREFERENCED_PARAMETER(timer);

	if (GetRoot()->IsAttack())
	{
		//	����U��
		SetRotate(GetRotate() * DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(Utility::CreateRandom(-4.f, 4.f))));
	}
	else
	{
		SetRotate(DirectX::SimpleMath::Quaternion::Lerp(GetRotate(), DirectX::SimpleMath::Quaternion::Identity, 0.3f));
	}

	if (GetRoot()->IsWalk())
	{
		//	�������E�O��ɗh�炷
		SetPosition(GetPosition() + DirectX::SimpleMath::Vector3(Utility::CreateRandom(-SHAKE_VOLUME, SHAKE_VOLUME), 0.0f, Utility::CreateRandom(-SHAKE_VOLUME, SHAKE_VOLUME)));
	}

	SetPosition(DirectX::SimpleMath::Vector3::Lerp(GetPosition(), DirectX::SimpleMath::Vector3::Zero, 0.1f));
}
 
/// <summary>
/// ���S�A�j���[�V����
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void PlayerHead::DeathAnimation(const DX::StepTimer& timer)
{
	UNREFERENCED_PARAMETER(timer);

	using namespace DirectX::SimpleMath;

	if (GetPosition().y <= GROUND_HEAD_POSITION)
	{
		m_elapsedTime += static_cast<float>(timer.GetElapsedSeconds());

		//	�͂��L��]���Ă���̂Ȃ猸�Z
		if (m_excessiveForce <= 0.0f)
		{
			//	�ړ���
			Vector3 vel = Vector3(0.0f, 0.0f, m_excessiveForce);
			//	�ړ��ʂ𑫂�
			SetPosition(GetPosition() + Vector3::Transform(vel, GetRoot()->GetRotate()));
		
			//	�͂���߂�
			m_excessiveForce += static_cast<float>(timer.GetElapsedSeconds());
		}
		else
		{
			m_excessiveForce = 0.0f;
		}

		//	������]������
		SetRotate(GetRotate() * Quaternion::CreateFromAxisAngle(Vector3::UnitY, DirectX::XMConvertToRadians(5.0f)));

		return;
	}

	SetPosition(GetPosition() + Vector3::Transform(DEATH_ACCELERATION, GetRoot()->GetRotate()));
}

/// <summary>
/// �����A�j���[�V����
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void PlayerHead::WinAnimation(const DX::StepTimer& timer)
{
	using namespace DirectX::SimpleMath;

	m_elapsedTime += static_cast<float>(timer.GetElapsedSeconds());
	SetPosition(Vector3(0.0f, 0.0f, sinf(m_elapsedTime * 3.0f) * 0.1f));
}

/// <summary>
/// ���f���̕`��
/// </summary>
/// <param name="model">���f��</param>
/// <param name="world">���[���h</param>
/// <param name="view">�r���[</param>
/// <param name="proj">�v���W�F�N�V����</param>
void PlayerHead::DrawModel(DirectX::Model* model, const DirectX::SimpleMath::Matrix& world, const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	UNREFERENCED_PARAMETER(world);
	UNREFERENCED_PARAMETER(model);

	//	�ړ��s��
	DirectX::SimpleMath::Matrix trans = DirectX::SimpleMath::Matrix::CreateTranslation(GetRoot()->GetPosition() + GetPosition());
	//	��]�s��
	DirectX::SimpleMath::Matrix rotate = DirectX::SimpleMath::Matrix::CreateFromQuaternion(GetRoot()->GetRotate() * GetRotate());
	//	�g��s��
	DirectX::SimpleMath::Matrix scale = DirectX::SimpleMath::Matrix::CreateScale(GetRoot()->GetScale());
	//	���[���h
	DirectX::SimpleMath::Matrix wrd = scale * rotate * trans;
	//	���f���̕`��
	PlayerComponent::DrawModel(m_model, wrd, view, proj);
}