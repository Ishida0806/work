//
//		File Name �F NormalEnemy.cpp
//		Production�F 2023/11/12
//		Author�@�@�F �Γc ����	
// 
//		�ʏ�̓G�̃N���X
//	
#include "pch.h"
#include "NormalEnemy.h"

#include "Game/MyLib/Scenes/PlayScene/Object/Bullet/BulletFactroy.h"

//	�G���������x
const float NormalEnemy::ENEMY_SPEED							= 0.047f;
//	�U���������
const float NormalEnemy::LERP_SPEED								= 0.03f;
//	�N�����v�p�̕�
const float NormalEnemy::WALL_PLACE								= 23.5f;
//	�G�������Ă���e�̐�
const int   NormalEnemy::ENEMY_BULLETS_NUM						= 100;
//	����ł܂ł̃J�E���g
const float NormalEnemy::SHOT_TIME								= 0.86f;
//	�����_���ňړ��������ς�鎞��
const float NormalEnemy::RANDOM_TIME							= 3.5f;
//	�ŏ��ɗ^�������
const int   NormalEnemy::FIRST_POWER							= 2;
//	�����ݒ�̗̑�
const int   NormalEnemy::FIRST_HEALTH							= 15;
//	�m�[�}���̌o���l
const int   NormalEnemy::NORMAL_EXP								= 3;
//	���S�A�j���[�V�����̍ۂɈ����l
const float NormalEnemy::SHADOW_ARGUMENT						= 0.02f;
//	�����蔻��
const Collision::Shape::Sphere	   NormalEnemy::SPERE_COLLISION		= Collision::Shape::Sphere(DirectX::SimpleMath::Vector3::Zero, 0.6f);
//	����̍��G�͈�
const Collision::Shape::Sphere	   NormalEnemy::SEARCH_COLLISION	= Collision::Shape::Sphere(DirectX::SimpleMath::Vector3::Zero, 10.2f);
//	����̔��ˉ\�͈�
const Collision::Shape::Sphere	   NormalEnemy::SHOT_COLLISION		= Collision::Shape::Sphere(DirectX::SimpleMath::Vector3::Zero, 9.6f);
//	���S�A�j���[�V�����̍ۂɈ����l
const DirectX::SimpleMath::Vector3 NormalEnemy::SCALE_ARGUMENT		= DirectX::SimpleMath::Vector3(0.01f, 0.01f, 0.01f);
//	�ʏ�̑傫��
const DirectX::SimpleMath::Vector3 NormalEnemy::DEFAULT_SCALE		= DirectX::SimpleMath::Vector3(0.55f, 0.55f, 0.55f);

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="position">���W</param>
/// <param name="helath">�̗�</param>
/// <param name="power">��</param>
/// <param name="level">���x��</param>
/// <param name="obj">�I�u�W�F�N�g�̃^�C�v</param>
NormalEnemy::NormalEnemy(const DirectX::SimpleMath::Vector3& position, const int& helath, const int& power, const int& level, ObjectType obj)
	:
	Enemy(position, helath, power, NORMAL_EXP), 
	m_level(level),
	m_objType(obj),
	m_isShot(false),
	m_inShot(false),
	m_direction(Direction::BOTTOM),
	m_shotInterval(0.0f),
	m_shotCoolTime(0.0f),
	m_shadowScale(1.2f)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
NormalEnemy::~NormalEnemy()
{
}

/// <summary>
/// ����������
/// </summary>
void NormalEnemy::Initialize()
{
	//	�G�̃��f�����擾
	m_enemyModel = MyLib::ResourcesData::GetInstance()->GatModel(L"normalEnemy");
	//	�ʏ�̑傫����
	SetScale(DEFAULT_SCALE);
	//	�G�̑����쐬
	m_enemyLeg = std::make_unique<EnemyLeg>(this, MyLib::ResourcesData::GetInstance()->GatModel(L"normalEnemyLeg"));
	//	����������
	m_enemyLeg->Initialize();

	//	����̒ǉ�
	Enemy::AddColisionEnemy
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
void NormalEnemy::Update(const DX::StepTimer& timer)
{
	using namespace DirectX::SimpleMath;

	//	�����Ă��邩
	IsAlive();

	//	�n�ʂɖ�����Ȃ��悤��
	SetPosition(Vector3(GetPosition().x, 0.0f, GetPosition().z));

	///	���S�A�j���[�V�������Ȃ珈�����s��Ȃ�
	if (IsDeadAnimation())	return;

	//	�ǔ���Ԃɓ���܂ō��G���[�h�ɂ���
	if (!IsHate())
	{
		//	�G�������ړ�������
		AutoMove(timer, ENEMY_SPEED, LERP_SPEED);
	}
	else
	{
		//	�v���C���[��ǔ�
		HateMode(timer);
	}

	//	���ˎ��̃A�j���[�V����
	m_shotAnimationScale = DirectX::SimpleMath::Vector3::Lerp(m_shotAnimationScale, DirectX::SimpleMath::Vector3(m_shotInterval / 2.8f, m_shotInterval / 2.8f, 0.0f), 0.1f);
	//	���ˎ��̃A�j���[�V����
	m_shotAnimationAfterScale = DirectX::SimpleMath::Vector3::Lerp(m_shotAnimationAfterScale, DirectX::SimpleMath::Vector3(0.0f, -m_shotCoolTime / 3.6f, 0.0f), 0.1f);

	// ���N���X��ݒ肷��
	Enemy::Update(timer);

	//	������
	m_enemyLeg->RollLeg(timer, 7.0f);
}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="view">�r���[</param>
/// <param name="proj">�v���W�F�N�V����</param>
void NormalEnemy::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	auto screen = MyLib::ScreenResources::GetInstance();
	//	���̕`��
	m_enemyLeg->Render(view, proj);
	//	�ۉe�����
	CreateShadow(view, proj, m_shadowScale);
	// �X�P�[���s��
	DirectX::SimpleMath::Matrix scale = DirectX::SimpleMath::Matrix::CreateScale(GetScale() + m_shotAnimationScale + m_shotAnimationAfterScale);
	// �ʒu�s��
	DirectX::SimpleMath::Matrix trans = DirectX::SimpleMath::Matrix::CreateTranslation(GetPosition());
	// ��]�s��
	DirectX::SimpleMath::Matrix rotate = DirectX::SimpleMath::Matrix::CreateFromQuaternion(GetRotate()); 
	// ���[���h�ϊ��s��ɕϊ��i�X�P�[���A��]�A�ʒu�̏��œK�p�j
	DirectX::SimpleMath::Matrix world = scale * rotate * trans;
	// �G�����G��Ԃ܂��͎��S�A�j���[�V�������̏ꍇ�A����ȕ`����s��
	if (IsDeadAnimation())
	{
		m_enemyModel->Draw(screen->GetDeviceContext(), *screen->GetCommonState(), world, view, proj, true);
	}
	else // �ʏ�̕`����s���܂�
	{
		m_enemyModel->Draw(screen->GetDeviceContext(), *screen->GetCommonState(), world, view, proj);
	}

	Enemy::Render(view, proj);
}

/// <summary>
/// �I������
/// </summary>
void NormalEnemy::Finalize()
{
}

/// <summary>
/// ������ʂ�ݒ肷��
/// </summary>
/// <param name="flag"></param>
void NormalEnemy::SetAbility(const bool& flag)
{
	m_isShot = flag;
}

/// <summary>
/// �����Ă��邩�H
/// </summary>
void NormalEnemy::IsAlive()
{
	//	����ł��Ȃ��Ȃ�A��
	if (GetHealth() >= 0)	return;

	//	�f�X�A�j���[�V�����O�ɉ����o��
	if (!IsDeadAnimation())
		//	SE���Đ�����
		AudioManager::GetInstance()->PlaySoundEffectSE(L"Deth_AnimationSE01");

	//	���S�A�j���[�V���������s
	StartDeathAnimation();

	//	���g�̑傫���Ɖe�̑傫�����k��
	SetScale(GetScale() - SCALE_ARGUMENT);
	m_shadowScale -= SHADOW_ARGUMENT;
	//	�A�j���[�V�����̓[���ɂ���
	m_shotAnimationScale = DirectX::SimpleMath::Vector3::Zero;

	if (GetScale().x < 0.0f && GetScale().y < 0.0f && GetScale().z < 0.0f)
	{
		//	0�ȉ��Ȃ�E��
		DeathObject();
	}	
}

/// <summary>
/// �ǔ����[�h
/// </summary>
/// <param name="timer"></param>
void NormalEnemy::HateMode(const DX::StepTimer& timer)
{

	if (m_shotCoolTime > 0.0f)
	{
		m_shotCoolTime -= static_cast<float>(timer.GetElapsedSeconds()); 
		return;
	}
	//	�v���C���[������悤�ɂ���
	SetRotate(DirectX::SimpleMath::Quaternion::Lerp(GetRotate(), GetObjectiveRotate(), LERP_SPEED));

	//	���ˌ����ɓ����Ă��Ȃ�������Ǐ]����
	if (!InAbility() && !m_inShot)
	{
		//	�����Ă���
		SetWalk(true);
		//	���ˌ������班���ł��������珉����
		//	m_shotInterval = 0.0f;
		// �������Z�o����
		DirectX::SimpleMath::Vector3 direction = GetTargetPosition() - GetPosition();
		//	������������x�z���Ă���Ȃ�ǔ����[�h���甲����
		if (abs(direction.Length()) > 25.0f)
		{
			SetHate(false);
		}

		// �x�N�g���𐳋K�����đ��x��������
		direction.Normalize();
		DirectX::SimpleMath::Vector3 vel = direction * ENEMY_SPEED;

		//	�ړ��ʂ𑫂�
		SetVelocity(vel);
	}
	else
	{
		//	�����Ă��Ȃ�
		SetWalk(false);

		//	���ˌ����ɓ�����
		m_inShot = true;

		//	�o�ߎ��Ԃ𑫂�
		m_shotInterval += static_cast<float>(timer.GetElapsedSeconds());

		//	���˔͈͂ɓ����Ă���Ȃ�e�𔭎˂���
		if (m_shotInterval <= SHOT_TIME)	return;

		m_isShot	   = true;
		m_inShot	   = false;
		m_shotInterval = 0.0f;
		m_shotCoolTime = 1.0f;
	}
}