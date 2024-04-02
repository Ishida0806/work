//
//		File Name �F Sord.cpp
//		Production�F 2023/6/19
//		Author�@�@�F �Γc ����
// 
//		���̓���E�`����܂Ƃ߂��N���X	
//	
#include "pch.h"
#include "Sord.h"
#include "../Player.h"

//	�I�t�Z�b�g�p�x
const float Sord::OFFSET_ANGLE			= 120.0f;
//	������U�������鎞�̊p�x
const float Sord::SWING_ANGLE			= 150.0f;
//	�U�鑬�x
const float Sord::SWING_SPEED			= 0.34f;
//	���̔��a
const float Sord::SPHERE_RADIUS			= 0.1f;
//	���[�v�̎���
const float Sord::LERP_TIME				= 0.4f;
//	�U����̃N�[���^�C��
const float Sord::ATTACK_COOL_TIME		= 0.2f;
//	�U��������x
const float Sord::TURN_SPEED			= 0.12f;
//	����U��I���Ď��ɐU���܂ł̎���		
const float Sord::SWING_COOLTIME		= 0.54f;
//	����U����ڂ�U���\����	
const float Sord::SWING_SECOND_CHANCE	= SWING_COOLTIME / 2.0f;
//	���̒n�ʂ̈ʒu
const float Sord::GROUND_SORD_POSITION  = -0.082f;
//	�����̎n��
const DirectX::SimpleMath::Vector3 Sord::SEGMENT_LENGTH_START	= DirectX::SimpleMath::Vector3(0.0f, 5.0f, 0.0f);
//	�����̏I���
const DirectX::SimpleMath::Vector3 Sord::SEGMENT_LENGTH_END		= DirectX::SimpleMath::Vector3(0.0f,  0.3f, 0.0f);
//	���̃I�t�Z�b�g�ʒu
const DirectX::SimpleMath::Vector3 Sord::SORD_OFFSET_POSITION	= DirectX::SimpleMath::Vector3(0.25f, 0.5f, 0.0f);
//	�����]�������
const DirectX::SimpleMath::Vector3 Sord::SORD_ROLL_DIRECTION	= DirectX::SimpleMath::Vector3(0.0f, 0.0f, -0.02f);
//	���̗����鑬�x
const DirectX::SimpleMath::Vector3 Sord::SORD_FALL_SPEED		= DirectX::SimpleMath::Vector3(0.0f, -0.011f, 0.0f);

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="parent">�e</param>
Sord::Sord(Player* parent)
	:m_parent(parent),
	m_sordModel(nullptr),
	m_attackTime(SWING_COOLTIME),
	m_slashAngle(0.0f),
	m_objective(0.0f),
	m_attackCoolTime(0.0f),
	m_isAttack(false),
	m_isAttackCoolTime(false),
	m_secondAttack(false)
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Sord::~Sord()
{
}

/// <summary>
/// ����������
/// </summary>
void Sord::Initialize()
{
	CreateDeviceDependentResources();
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void Sord::Update(const DX::StepTimer& timer)
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
void Sord::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	//	�R�����X�e�[�g
	DirectX::CommonStates* state				 = MyLib::ScreenResources::GetInstance()->GetCommonState();
	//	�R���e�L�X�g
	auto context								 = MyLib::ScreenResources::GetInstance()->GetDeviceContext();

	// �ړ��s��̍쐬
	DirectX::SimpleMath::Matrix  trans;

	if (m_parent->IsDeathAnimation())
	{
		trans = DirectX::SimpleMath::Matrix::CreateTranslation(GetPosition());
	}
	else
	{
		trans = DirectX::SimpleMath::Matrix::CreateTranslation(m_parent->GetPosition() + SORD_OFFSET_POSITION);
	}	
	// ��]�s��̍쐬
	DirectX::SimpleMath::Matrix  rotation = DirectX::SimpleMath::Matrix::CreateFromQuaternion(GetRotate() * m_slashRotate * m_offsetRotate );
	// ���[���h�s��̍쐬�i��]�A�ړ���K�p�j
	m_sordMatrix = rotation * trans;
	// ���f���̕`��
	m_sordModel->Draw
	(
		context,
		*state,
		m_sordMatrix,
		view, 
		proj
	);
}

/// <summary>
/// �I������
/// </summary>
void Sord::Finalize()
{
}

/// <summary>
/// �f�o�C�X�ˑ��̕���������
/// </summary>
void Sord::CreateDeviceDependentResources()
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
void Sord::Attack(const DX::StepTimer& timer)
{
	//	�o�ߎ��Ԃ𑫂�
	float elapsedTime = static_cast<float>(timer.GetElapsedSeconds());

	//auto mouse = MyLib::InputSystem::GetInstance()->GetStateTracker();

	//	�U���N�[���^�C���͔��������H
	if (m_isAttackCoolTime)
	{
		//	�o�ߎ��Ԃ�����
		m_attackCoolTime -= elapsedTime;

		//	�I����Ă���Ȃ璼���ɏI������ && ���Ȃ��Ȃ�A��
		if (m_attackCoolTime < 0.0f)
		{
			m_isAttackCoolTime = false;
		}
		else
		{
			return;
		}
	}

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
	//	�o�ߎ��Ԃ�����
	m_attackTime -= elapsedTime;
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
		m_attackTime	   = SWING_COOLTIME;
		m_attackCoolTime   = ATTACK_COOL_TIME;
		m_slashAngle	   = 0.0f;
		m_objective		   = 0.0f;
		m_secondAttack	   = false;
		m_isAttack		   = false;
		m_isAttackCoolTime = true;
	}
}

/// <summary>
/// ���[�v���J�n����
/// </summary>
void Sord::AttackLerp()
{
	DirectX::SimpleMath::Quaternion slashRotate = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitX, DirectX::XMConvertToRadians(m_slashAngle));
	m_slashRotate								= DirectX::SimpleMath::Quaternion::Lerp(m_slashRotate, slashRotate, LERP_TIME);
}

/// <summary>
/// �����蔻����X�V
/// </summary>
void Sord::UpdateColison()
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
void Sord::UpdateSordLerp()
{
	//	�v���C���[�̉�]�p��X��
	DirectX::SimpleMath::Quaternion playerRotate = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitX, m_parent->GetRotate().ToEuler().y);
	SetRotate(DirectX::SimpleMath::Quaternion::Lerp(GetRotate(), playerRotate, TURN_SPEED));
}


/// <summary>
/// ���̎��S���̃A�j���[�V����
/// </summary>
void Sord::SordDeathAniamtion()
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
bool Sord::ShouldSwingStartFlag()
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
bool Sord::ShouldSwingSecondFlag()
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
