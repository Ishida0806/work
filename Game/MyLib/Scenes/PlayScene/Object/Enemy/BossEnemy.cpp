//
//		File Name �F BossEnemy.cpp
//		Production�F 2023/11/12
//		Author�@�@�F �Γc ����	
// 
//		�{�X�̓G�̃N���X
//	
#include "pch.h"
#include "BossEnemy.h"

#include "Game/MyLib/Scenes/PlayScene/Object/Bullet/BulletFactroy.h"

//	�G���������x
const float						BossEnemy::BOSS_SPEED		= 0.04f;
//	�U���������
const float						BossEnemy::LERP_SPEED		= 0.03f;
//	�N�����v�p�̕�
const float						BossEnemy::WALL_PLACE		= 23.5f;
//	�G�������Ă���e�̐�
const int						BossEnemy::BOSS_BULLETS_NUM	= 50;
//	�{�X�̌o���l
const int						BossEnemy::BOSS_EXP			= 30;
//	����ł܂ł̃J�E���g
const float						BossEnemy::SHOT_TIME		= 0.71f;
//	�ŏ��ɗ^�������
const int						BossEnemy::FIRST_POWER		= 1;
//	�����ݒ�̗̑�
const int						BossEnemy::FIRST_HEALTH		= 30;
//	�e�̑傫��
const float						BossEnemy::SHADOW_SCALE		= 7.2f;
//	���S�A�j���[�V�����̍ۂɈ����l
const float						BossEnemy::SHADOW_ARGUMENT	= 0.072f;
//	���S�A�j���[�V�����̍ۂɈ����l
const float						BossEnemy::SCALE_ARGUMENT	= 0.01f;
//	�����蔻��
const Collision::Shape::Sphere	BossEnemy::SPERE_COLLISION	= Collision::Shape::Sphere(DirectX::SimpleMath::Vector3::Zero, 1.2f);
//	����̍��G�͈�
const Collision::Shape::Sphere	BossEnemy::SEARCH_COLLISION = Collision::Shape::Sphere(DirectX::SimpleMath::Vector3::Zero, 15.0f);
//	����̔��ˉ\�͈�
const Collision::Shape::Sphere	BossEnemy::SHOT_COLLISION	= Collision::Shape::Sphere(DirectX::SimpleMath::Vector3::Zero, 13.5f);

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="position">���W</param>
/// <param name="helath">�̗�</param>
/// <param name="power">��</param>
/// <param name="level">���x��</param>
/// <param name="obj">�I�u�W�F�N�g�̃^�C�v</param>
BossEnemy::BossEnemy(const DirectX::SimpleMath::Vector3& position, const int& helath, const int& power, const int& level, ObjectType obj)
	:
	Enemy(position, helath, power, BOSS_EXP), 
	m_level(level),
	m_objType(obj),
	m_isShot(false),
	m_isSeartch(false),
	m_direction(Direction::BOTTOM),
	m_shadowScale(SHADOW_SCALE),
	m_scale(1.0f),
	m_randomTime(0.0f),
	m_shotInterval(0.0f)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BossEnemy::~BossEnemy()
{
}

/// <summary>
/// ����������
/// </summary>
void BossEnemy::Initialize()
{
	//	�G�̃��f�����擾
	m_bossModel = MyLib::ResourcesData::GetInstance()->GatModel(L"bossEnemy");
	//	�����蔻��̒ǉ�
	AddColisionEnemy
	(
		SPERE_COLLISION,
		SEARCH_COLLISION,
		SHOT_COLLISION
	);
	//	���ʎq��ݒ肷��
	SetType(m_objType);
	//	���N���X�̏�����
	Enemy::Initialize();
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void BossEnemy::Update(const DX::StepTimer& timer)
{
	//	�����Ă��邩
	IsAlive();

	///	���S�A�j���[�V�������Ȃ珈�����s��Ȃ�
	if (IsDeadAnimation())	return;

	//	�ǔ���Ԃɓ���܂ō��G���[�h�ɂ���
	if (!IsHate())
	{
		//	�G�������ړ�������
		AutoMove(timer, BOSS_SPEED, LERP_SPEED);
	}
	else
	{
		//	�v���C���[��ǔ�
		HateMode(timer);
	}

	// �ǔ���
	Enemy::Update(timer);
}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="view">�r���[</param>
/// <param name="proj">�v���W�F�N�V����</param>
void BossEnemy::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	auto screen = MyLib::ScreenResources::GetInstance();

	//	�ۉe���쐬
	CreateShadow(view, proj, m_shadowScale);

	DirectX::SimpleMath::Matrix scale	= DirectX::SimpleMath::Matrix::CreateScale(m_scale);
	DirectX::SimpleMath::Matrix trans	= DirectX::SimpleMath::Matrix::CreateTranslation(GetPosition());
	DirectX::SimpleMath::Matrix rotate  = DirectX::SimpleMath::Matrix::CreateFromQuaternion(GetRotate());

	DirectX::SimpleMath::Matrix world	= scale * rotate * trans;

	if (IsDeadAnimation())
	{
		m_bossModel->Draw(screen->GetDeviceContext(), *screen->GetCommonState(), world, view, proj, true);
	}
	else
	{
		m_bossModel->Draw(screen->GetDeviceContext(), *screen->GetCommonState(), world, view, proj);
	}
}

/// <summary>
/// �I������
/// </summary>
void BossEnemy::Finalize()
{
}

/// <summary>
/// ������ʂ�ݒ肷��
/// </summary>
/// <param name="flag"></param
void BossEnemy::SetAbility(const bool& flag)
{
	m_isShot = flag;
}

/// <summary>
/// �����Ă��邩�H
/// </summary>
void BossEnemy::IsAlive()
{
	//	�̗͂�0�ȉ��Ȃ玀�S�A�j���[�V�������s��
	if (GetHealth() >= 0)	return;
	
	//	�f�X�A�j���[�V�����O�ɉ����o��
	if (!IsDeadAnimation())
	//	SE���Đ�����
	AudioManager::GetInstance()->PlaySoundEffectSE(L"Deth_AnimationSE01");

	//	���S�A�j���[�V���������s
	StartDeathAnimation();

	//	�e�Ǝ��g�̑傫�����k������
	m_shadowScale -= SHADOW_ARGUMENT;
	m_scale		  -= SCALE_ARGUMENT;

	if (m_scale < 0.0f)
	{
		//	0�ȉ��Ȃ�E��
		DeathObject();
	}	
}

/// <summary>
/// �ǔ����
/// </summary>
/// <param name="timer">�^�C�}�[�@�@</param>
void BossEnemy::HateMode(const DX::StepTimer& timer)
{

	auto offset = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(90.0f));

	SetRotate(DirectX::SimpleMath::Quaternion::Lerp(GetRotate(), GetObjectiveRotate() * offset, LERP_SPEED));

	//	���ˌ����ɓ����Ă��Ȃ�������Ǐ]����
	if (!InAbility())
	{
		//	���ˌ������班���ł��������珉����
		m_shotInterval = 0.0f;
		// �L�����N�^�[�̈ʒu����ڕW�ʒu�ւ̃x�N�g�����v�Z
		DirectX::SimpleMath::Vector3 direction = GetTargetPosition() - GetPosition();
		// �x�N�g���𐳋K�����đ��x��������
		direction.Normalize();
		DirectX::SimpleMath::Vector3 velocity = direction * BOSS_SPEED;
		// �ʒu���X�V
		SetVelocity(velocity);
	}
	else
	{
		// �L�����N�^�[�̈ʒu����ڕW�ʒu�ւ̃x�N�g�����v�Z
		DirectX::SimpleMath::Vector3 direction = GetTargetPosition() - GetPosition();
		//	����
		float distance = direction.Length();

		//	���̋�����ۂ�
		if (distance >= 12.0f)
		{
			// �x�N�g���𐳋K�����đ��x��������
			direction.Normalize();
			DirectX::SimpleMath::Vector3 velocity = direction * BOSS_SPEED;
			// �ʒu���X�V
			SetVelocity(velocity);
		}
		else
		{
			// �x�N�g���𐳋K�����đ��x��������
			direction.Normalize();
			DirectX::SimpleMath::Vector3 velocity = direction * BOSS_SPEED;
			// �ʒu���X�V
			SetVelocity(-velocity);
		}

		m_shotInterval += static_cast<float>(timer.GetElapsedSeconds());

		//	���˔͈͂ɓ����Ă���Ȃ�e�𔭎˂���
		if (m_shotInterval <= SHOT_TIME)	return;
		
		m_isShot = true;
		m_shotInterval = 0.0f;
	}
}