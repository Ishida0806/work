//
//		File Name �F Wepon.cpp
//		Production�F 2023/6/19
//		Author�@�@�F �Γc ����
// 
//		���̓���E�`����܂Ƃ߂��N���X	
//	
#include "pch.h"
#include "Wepon.h"
#include "../Player.h"

//	�I�t�Z�b�g�p�x
const float Wepon::OFFSET_ANGLE			= 120.0f;
//	������U�������鎞�̊p�x
const float Wepon::SWING_ANGLE			= 150.0f;
//	�U�鑬�x
const float Wepon::SWING_SPEED			= 0.34f;
//	���̔��a
const float Wepon::SPHERE_RADIUS		= 0.1f;
//	���[�v�̎���
const float Wepon::LERP_TIME			= 0.4f;
//	�U��������x
const float Wepon::TURN_SPEED			= 0.12f;
//	����U��I���Ď��ɐU���܂ł̎���		
const float Wepon::SWING_COOLTIME		= 0.54f;
//	����U����ڂ�U���\����	
const float Wepon::SWING_SECOND_CHANCE	 = SWING_COOLTIME / 2.0f;
//	���̒n�ʂ̈ʒu
const float Wepon::GROUND_SORD_POSITION  = -0.082f;
//	�����̎n��
const DirectX::SimpleMath::Vector3 Wepon::SEGMENT_LENGTH_START	= DirectX::SimpleMath::Vector3(0.0f, 5.0f, 0.0f);
//	�����̏I���
const DirectX::SimpleMath::Vector3 Wepon::SEGMENT_LENGTH_END		= DirectX::SimpleMath::Vector3(0.0f,  0.3f, 0.0f);
//	���̃I�t�Z�b�g�ʒu
const DirectX::SimpleMath::Vector3 Wepon::SORD_OFFSET_POSITION	= DirectX::SimpleMath::Vector3(0.25f, 0.4f, 0.0f);
//	�����]�������
const DirectX::SimpleMath::Vector3 Wepon::SORD_ROLL_DIRECTION	= DirectX::SimpleMath::Vector3(0.0f, 0.0f, -0.02f);
//	���̗����鑬�x
const DirectX::SimpleMath::Vector3 Wepon::SORD_FALL_SPEED		= DirectX::SimpleMath::Vector3(0.0f, -0.011f, 0.0f);

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="parent">�e</param>
Wepon::Wepon(Player* parent)
	:m_parent(parent),
	m_sordModel(nullptr),
	m_attackTime(SWING_COOLTIME),
	m_slashAngle(0.0f),
	m_objective(0.0f),
	m_isAttack(false),
	m_secondAttack(false)
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Wepon::~Wepon()
{
}

/// <summary>
/// ����������
/// </summary>
void Wepon::Initialize()
{
	CreateDeviceDependentResources();
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void Wepon::Update(const DX::StepTimer& timer)
{
    //  �U�����J�n
	Attack(timer);
	//	�U�����������̂��ړ�
	AttackLerp();
	//	�����蔻����X�V
	UpdateColison();
	//	���̉�]�p���X�V����
	UpdateSordLerp();
}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="view">�r���[</param>
/// <param name="proj">�v���W�F�N�V����</param>
void Wepon::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	UNREFERENCED_PARAMETER(view);
	UNREFERENCED_PARAMETER(proj);
}

/// <summary>
/// �I������
/// </summary>
void Wepon::Finalize()
{
}

/// <summary>
/// �f�o�C�X�ˑ��̕���������
/// </summary>
void Wepon::CreateDeviceDependentResources()
{
	//	���̃��f�����擾����
	m_sordModel = MyLib::ResourcesData::GetInstance()->GatModel(L"Sord");
	//	�����蔻��̔��a��������
	m_sordCapusel.radius		= SPHERE_RADIUS;
	//	�����̍ŏ�
	m_sordCapusel.segment.start = SEGMENT_LENGTH_START;
	//	�����̍Ō�
	m_sordCapusel.segment.end	= SEGMENT_LENGTH_END;
	//	��]�̃I�t�Z�b�g�l
	m_offsetRotate = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitZ, DirectX::XMConvertToRadians(90.0f)) *
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY,			   DirectX::XMConvertToRadians((-150.0f)));
	//	���ʎq��o�^����
	SetType(ObjectType::Sord);
}

/// <summary>
/// �U��
/// </summary>
/// <param name="timer"></param>
void Wepon::Attack(const DX::StepTimer& timer)
{
	//	�U�������𖞂����Ă��邩
	if (ShouldSwingStartFlag())
	{
		m_isAttack = true;
		m_objective = m_slashAngle + SWING_ANGLE;
		//	�����Đ�����
		AudioManager::GetInstance()->PlaySoundEffectSE(L"Swing_Sword_SE01");
	}

	//	�U��������Ȃ��Ȃ珈�����s��Ȃ�
	if (!m_isAttack)	return;

	//	�o�ߎ��Ԃ𑫂�
	m_attackTime -= static_cast<float>(timer.GetElapsedSeconds());
	//	���[�v������
	m_slashAngle = Utility::Lerp(m_slashAngle, m_objective, SWING_SPEED);

	//	�U������
	if (m_attackTime > 0.0f && m_attackTime <= SWING_SECOND_CHANCE && ShouldSwingSecondFlag())
	{
		m_attackTime += SWING_COOLTIME / 2.f;
		m_secondAttack = true;
		m_objective -= SWING_ANGLE;

		//	�����Đ�����
		AudioManager::GetInstance()->PlaySoundEffectSE(L"Swing_Sword_SE02");		
	}

	//	�U�����I����܂ł̎���
	if (m_attackTime < 0.0f)
	{
		m_attackTime   = SWING_COOLTIME;
		m_slashAngle   = 0.0f;
		m_objective	   = 0.0f;
		m_isAttack	   = false;
		m_secondAttack = false;
	}
}

/// <summary>
/// ���[�v���J�n����
/// </summary>
void Wepon::AttackLerp()
{
	DirectX::SimpleMath::Quaternion slashRotate = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitX, DirectX::XMConvertToRadians(m_slashAngle));
	m_slashRotate								= DirectX::SimpleMath::Quaternion::Lerp(m_slashRotate, slashRotate, LERP_TIME);
}

/// <summary>
/// �����蔻����X�V
/// </summary>
void Wepon::UpdateColison()
{
	//	�����̍ŏ��ƍŌ�̒l��������
	m_sordCapusel.segment.start = SEGMENT_LENGTH_START;
	m_sordCapusel.segment.end	= SEGMENT_LENGTH_END;
	//	���ݒn�ɓ����蔻���傫�����ړ�����
	m_sordCapusel.segment.start = DirectX::SimpleMath::Vector3::Transform(m_sordCapusel.segment.start, m_sordMatrix);
	m_sordCapusel.segment.end	= DirectX::SimpleMath::Vector3::Transform(m_sordCapusel.segment.end,   m_sordMatrix);
}

/// <summary>
/// ���̉�]�p���X�V����
/// </summary>
void Wepon::UpdateSordLerp()
{
	DirectX::SimpleMath::Quaternion playerRotate = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitX, *m_cursolAngle);
	SetRotate(DirectX::SimpleMath::Quaternion::Lerp(GetRotate(), playerRotate, TURN_SPEED));
}


/// <summary>
/// ���̎��S���̃A�j���[�V����
/// </summary>
void Wepon::SordDeathAniamtion()
{
	using namespace DirectX::SimpleMath;

	if (GetPosition().y <= GROUND_SORD_POSITION)
	{
		SetPosition(GetPosition() +  Vector3::Transform(SORD_ROLL_DIRECTION, m_parent->GetRotate()));

		return;
	}

	SetPosition(GetPosition() + SORD_FALL_SPEED);
}

/// <summary>
/// �U����U��ŏ��̏����𖞂����Ă��邩
/// </summary>
/// <returns>�����𖞂����Ă��邩</returns>
bool Wepon::ShouldSwingStartFlag()
{
	auto mouse  = MyLib::InputSystem::GetInstance()->GetStateTracker();
	auto key	= MyLib::InputSystem::GetInstance()->GetKeyTracer();

	if (
		mouse->leftButton == mouse->PRESSED && !m_isAttack ||
		key->pressed.K && !m_isAttack
		)
	{
		return true;
	}

	return false;
}

/// <summary>
/// �U����U����ڂ̏����𖞂����Ă��邩
/// </summary>
/// <returns>�����𖞂����Ă��邩</returns>
bool Wepon::ShouldSwingSecondFlag()
{
	auto mouse = MyLib::InputSystem::GetInstance()->GetStateTracker();
	auto key   = MyLib::InputSystem::GetInstance()->GetKeyTracer();

	if (
		mouse->leftButton == mouse->PRESSED && !m_secondAttack && m_isAttack ||
		key->pressed.K						&& !m_secondAttack && m_isAttack
		)
	{
		return true;
	}

	return false;
}
