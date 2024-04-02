//
//		File Name �F Enemy.cpp
//		Production�F 2023/11/12
//		Author�@�@�F �Γc ����	
//	
#include "pch.h"
#include "Enemy.h"
#include "Game/MyLib/GameDatas/SteeringBehavior.h"

//	�����_���ňړ��������ς�鎞��
const float Enemy::RANDOM_TIME			= 1.8f;
//	�N�����v�p�̕�								  
const float Enemy::WALL_PLACE			= 23.5f;
//	�m�b�N�o�b�N
const float Enemy::ENEMT_TOUCH_REACTION = 0.055f;
//	���G�̎���
const float Enemy::INVINCIBLE_TIME		= 0.44f;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="position">���W</param>
/// <param name="helath">�̗�</param>
/// <param name="power">��</param>
/// <param name="enemyEXPoint">�G�̌o���l</param>
Enemy::Enemy(const DirectX::SimpleMath::Vector3& position, const int& helath, const int& power, const int& enemyEXPoint)
	:
	Object(position),
	m_helath(helath),
	m_maxHelath(helath),
	m_power(power),
	m_enemyEXPoint(enemyEXPoint),
	m_randomTime(RANDOM_TIME),
	m_invincibleTime(0.0f),
	m_wanderOrientation(0.0f),
	m_isHate(false),
	m_isWalk(false),
	m_isAlive(false),
	m_inAbility(false),
	m_isInvincible(false),
	m_deadAnimation(false),
	m_sphere{},
	m_searchSphere{},
	m_abilitySphere{}
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Enemy::~Enemy()
{
}

/// <summary>
/// ����������
/// </summary>
void Enemy::Initialize()
{
	ErrorCheck();

	//	�����蔻��̍X�V����
	UpdateColision();

	//	�ۉe�p
	m_primitive = DirectX::GeometricPrimitive::CreateSphere(MyLib::ScreenResources::GetInstance()->GetDeviceContext(), 1.0f);

	//	�n�[�g
	m_heart = std::make_unique<EnemyHeart>(this);
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void Enemy::Update(const DX::StepTimer& timer)
{
	using namespace DirectX::SimpleMath;

	//	�����Ă��邩
	IsAlive();

	// �U�����m�F�����疳�G
	Hit(timer);

	//	�n�[�g�̍X�V
	m_heart->Update(timer);

	// �ǔ���
	float x = Utility::Clamp(GetPosition().x, -WALL_PLACE, WALL_PLACE);
	float y = GetPosition().y;
	float z = Utility::Clamp(GetPosition().z, -WALL_PLACE, WALL_PLACE);

	// �����蔻��̍X�V
	UpdateColision();

	//	�N�����v�����l������
	SetPosition(Vector3(x, y, z));
}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="view">�r���[�v���W�F�N�V����</param>
/// <param name="proj">�r���[</param>
void Enemy::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	view;
	proj;

	//	�n�[�g�̕`��
	//m_heart->Render(view, proj);
}

/// <summary>
/// �ۉe���쐬
/// </summary>
/// <param name="view">�r���[</param>
/// <param name="proj">�v���W�F�N�V����</param>
void Enemy::CreateShadow(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj, const float& shadowScale)
{
	DirectX::SimpleMath::Matrix shadowWorld = DirectX::SimpleMath::Matrix::CreateScale(shadowScale, 0.001f, shadowScale) * DirectX::SimpleMath::Matrix::CreateTranslation(GetPosition().x, 0.01f, GetPosition().z + 1.0f);
	m_primitive->Draw(shadowWorld, view, proj, DirectX::SimpleMath::Color(0.0f, 0.0f, 0.0f, 0.5f));
}

/// <summary>
/// �I������
/// </summary>
void Enemy::Finalize()
{
}

/// <summary>
/// �����I�Ɉړ����s��
/// </summary>
/// <param name="timer"></param>
void Enemy::AutoMove(const DX::StepTimer& timer, const float& speed, const float& lookBackSpeed)
{
	using namespace DirectX;

	RandomMoveDirection(timer , speed);

	//	�����Ă���
	m_isWalk = true;

	//	�p�x�����[�v������
	SimpleMath::Quaternion rotate = SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitY, XMConvertToRadians(GetAngle()));
	SetRotate(SimpleMath::Quaternion::Lerp(GetRotate(), rotate, lookBackSpeed));

	//	�ړ��ʂ����W�ɑ���
	//SetVelocity(SteeringBehavior::Wander(this, &m_wanderOrientation, speed, 1.0f, 3.0f, 15.0f));
}

/// <summary>
/// �ڕW�̌������擾����
/// </summary>
/// <returns>����</returns>
DirectX::SimpleMath::Quaternion Enemy::GetObjectiveRotate()
{
	//	�������Z�o
	DirectX::SimpleMath::Vector3 dir = GetTargetPosition() - GetPosition();
	//	y���͎Q�Ƃ��Ȃ�
	dir.y = 0.0f;
	//	������Ԃ�
	return DirectX::SimpleMath::Quaternion::FromToRotation(DirectX::SimpleMath::Vector3::Forward, dir);
}

/// <summary>
/// �G���m�̐ڐG�ŋ����𗣂�
/// </summary>
/// <param name="direction"></param>
void Enemy::HitEnemyMove(const DirectX::SimpleMath::Vector3& direction)
{
	DirectX::SimpleMath::Vector3 vel = direction * ENEMT_TOUCH_REACTION;
	//	�ړ��ʂ𑫂�
	SetVelocity(vel);
}

/// <summary>
/// �_���[�W�^����
/// </summary>
/// <param name="damege">�_���[�W</param>
void Enemy::Damege(int damege)
{
	//	�_���[�W���̗͂����炷
	m_helath -= damege;

	//	���G�ɂ���
	m_isInvincible = true;

	//	���G�^�C�������Z�b�g����
	ResetInvincibleTime();

	if (IsHate())	return;

	//	�ǔ���Ԃ�
	m_isHate = true;
}

/// <summary>
///  ���[���h���x��
/// </summary>
/// <param name="health">���x��</param>
/// <param name="power">�p���[</param>
/// <param name="level">���x��</param>
void Enemy::StatusUP(const int& health, const int& power, const int& level)
{
	//	�̗͂����x�������₷
	m_helath = m_helath + (health * level);
	//	�͂�ݒ肷��
	m_power += power * level;
}

/// <summary>
/// �����_���ȕ����Ɍ�����ς���
/// </summary>
/// <param name="timer">�^�C�}�[</param>
/// <param name="speed">���x</param>
void Enemy::RandomMoveDirection(const DX::StepTimer& timer, const float& speed)
{
	using namespace DirectX;

	SimpleMath::Vector3 vel = SimpleMath::Vector3::Zero;

	m_randomTime += static_cast<float>(timer.GetElapsedSeconds());

	//	�o�߂Ō����Ă������ς���
	if (m_randomTime >= RANDOM_TIME)
	{
		//	4�����������_���Ō��߂�
		int randomDirection = rand() % 4;
		//	�o���l��[Direction]�^�ɃL���X�g
		Direction dir = static_cast<Direction>(randomDirection);
		//	���������߂�
		switch (dir)
		{
		case Direction::LEFT:		m_direction = Direction::LEFT;		break;
		case Direction::TOP:		m_direction = Direction::TOP;		break;
		case Direction::RIGHT:		m_direction = Direction::RIGHT;		break;
		case Direction::BOTTOM:		m_direction = Direction::BOTTOM;	break;
		default:														break;
		}
		//	�����_������܂ł̎��Ԃ�ς���
		m_randomTime = 0.0f;
	}

	//	�����_���Ŏw�肳�ꂽ�ق�������
	switch (m_direction)
	{
		//	�������̏ꍇ
	case Enemy::Direction::LEFT:
	{
		SetAngle(90.0f);
		vel.x -= speed;
		break;
	}
	//	������̏ꍇ
	case Enemy::Direction::TOP:
	{
		SetAngle(180.0f);
		vel.z += speed;
		break;
	}
	//	�E�����̏ꍇ
	case Enemy::Direction::RIGHT:
	{
		SetAngle(270.0f);
		vel.x += speed;
		break;
	}
	//	�������̏ꍇ
	case Enemy::Direction::BOTTOM:
	{
		SetAngle(0.0f);
		vel.z -= speed;
		break;
	}
	default:	break;
	}

	//	�ړ��ʂ����W�ɑ���
	SetVelocity(vel);
}

/// <summary>
/// �U�����m�F�����疳�G
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void Enemy::Hit(const DX::StepTimer& timer)
{
	// �������G�łȂ��Ȃ�A�������Ȃ�
	if (!m_isInvincible) return;

	// ���G���Ԃ��o�ߎ��Ԃ�������������
	m_invincibleTime += static_cast<float>(timer.GetElapsedSeconds());

	// �������G���Ԃ��w�肵�����Ԃ𒴂����牽�����Ȃ�
	if (m_invincibleTime <= INVINCIBLE_TIME)	return;

	// ���G���Ԃ��I������珉��������
	ResetInvincibleTime();
	// ���G��Ԃ���������
	m_isInvincible = false;
}

/// <summary>
/// �����蔻��̍X�V
/// </summary>
void Enemy::UpdateColision()
{
	DirectX::SimpleMath::Vector3 pos = GetPosition();
	pos.y = 0.5f;

	//	�����蔻��X�V
	m_sphere.center = pos;

	//�@���G�͈͂𔻒�X�V
	m_searchSphere.center = pos;

	//	�ˌ��͈͂𔻒�X�V
	m_abilitySphere.center = pos;
}

/// <summary>
/// �ڕW���W�̐ݒ肷��
/// </summary>
/// <param name="pos">�ڕW���W</param>
void Enemy::SetTargetPosition(const DirectX::SimpleMath::Vector3& pos)
{
	m_targetPos = pos;
}

/// <summary>
/// �w�C�g��Ԃ�ݒ肷��
/// </summary>
void Enemy::SetHate(const bool& flag)
{
	m_isHate = flag;
}

/// <summary>
/// ����Z�\�͈͂ɓ��������̃t���O�̐ݒ�
/// </summary>
/// <param name="flag">�t���O</param>
void Enemy::SetInAbility(const bool& flag)
{
	m_inAbility = flag;
}

/// <summary>
/// �����Ă��邩
/// </summary>
/// <param name="walk"></param>
void Enemy::SetWalk(const bool& walk)
{
	m_isWalk = walk;
}

/// <summary>
/// �w�C�g���[�h�ɂ���
/// </summary>
void Enemy::SetHateMode()
{
	m_isHate = true;
}

/// <summary>
/// ���G���Ԃ����Z�b�g����
/// </summary>
void Enemy::ResetInvincibleTime()
{
	m_invincibleTime = 0.0f;
}

/// <summary>
/// ���S�A�j���[�V�����̊J�n
/// </summary>
void Enemy::StartDeathAnimation()
{
	m_deadAnimation = true;
}

/// <summary>
/// ���S���m��
/// </summary>
void Enemy::DeathObject()
{
	m_isAlive = true;
}

/// <summary>
/// �����蔻��̒ǉ�
/// </summary>
/// <param name="colisionSpere">�����蔻��̍L��</param>
/// <param name="searchSpere">���G�͈�</param>
/// <param name="abilitySpere">����͈�</param>
void Enemy::AddColisionEnemy(const Collision::Shape::Sphere& colisionSpere, const Collision::Shape::Sphere& searchSpere, const Collision::Shape::Sphere& abilitySpere)
{
	m_sphere		= colisionSpere;
	m_searchSphere  = searchSpere;
	m_abilitySphere = abilitySpere;
}

/// <summary>
/// ���G����t���O
/// </summary>
/// <param name="flag">�t���O</param>
void Enemy::SetInvincibleFlag(bool flag)
{
	m_isInvincible = flag;
}

/// <summary>
/// �G���[���m�F����
/// </summary>
void Enemy::ErrorCheck()
{
	//	���������蔻�肪�ǉ�����Ă��Ȃ��Ȃ�~�߂�
	assert(m_sphere.radius > 0.0f);
	assert(m_searchSphere.radius > 0.0f);
	assert(m_abilitySphere.radius > 0.0f);
}

/// <summary>
/// �����Ă��邩�H
/// </summary>
void Enemy::IsAlive()
{

}