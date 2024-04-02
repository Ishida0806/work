//
//		File Name �F TackleEnemy.cpp
//		Production�F 2023/11/12
//		Author�@�@�F �Γc ����	
//	
#include "pch.h"
#include "TackleEnemy.h"

//	�G���������x
const float							  TackleEnemy::ENEMY_SPEED				= 0.05f;
//	�U���������
const float							  TackleEnemy::LOOK_BACK_SPEED			= 0.04f;
//	�ˌ��̑��x								    
const float							  TackleEnemy::ENEMY_TACLE_SPEED		= 0.36f;
//	�ڕW�l�Ƃ̋���
const float							  TackleEnemy::TACKLE_STOP_DISTANCE		= 0.8f;
//	�ːi��Ƃǂ܂鎞��					     
const float							  TackleEnemy::ALIVE_TIME				= 1.1f;
//	�ˌ��\�܂ł̎���
const float							  TackleEnemy::TACKLE_ENABLED_TIME		= 1.2f;
//	���S�A�j���[�V�����̍ۂɈ����l
const float							  TackleEnemy::SHADOW_ARGUMENT			= 0.02f;
//	�ˌ�����
const float							  TackleEnemy::TACKLE_DISTANCE			= 15.0f;
//	�X�^���^�C��
const float							  TackleEnemy::SWOON_TIME				= 2.4f;
//	�ŏ��ɗ^�������
const int							  TackleEnemy::FIRST_POWER				= 5;
//	�^�b�N���̌o���l
const int							  TackleEnemy::TACKLE_EXP				= 5;
//	�����ݒ�̗̑�
const int							  TackleEnemy::FIRST_HEALTH				= 25;
//	���S�A�j���[�V�����̍ۂɈ����l
const DirectX::SimpleMath::Vector3	  TackleEnemy::SCALE_ARGUMENT			= DirectX::SimpleMath::Vector3(0.01f, 0.01f, 0.01f);
//	�ʏ�̑傫��
const DirectX::SimpleMath::Vector3	  TackleEnemy::DEFAULT_SCALE			= DirectX::SimpleMath::Vector3(0.55f, 0.55f, 0.55f);
//	�����蔻��
const Collision::Shape::Sphere		  TackleEnemy::SPERE_COLLISION			= Collision::Shape::Sphere(DirectX::SimpleMath::Vector3::Zero, 0.5f);
//	����̍��G�͈�
const Collision::Shape::Sphere		  TackleEnemy::SEARCH_COLLISION			= Collision::Shape::Sphere(DirectX::SimpleMath::Vector3::Zero, 12.0f);
//	����̔��ˉ\�͈�
const Collision::Shape::Sphere		  TackleEnemy::TACKLE_COLLISION			= Collision::Shape::Sphere(DirectX::SimpleMath::Vector3::Zero, 9.7f);
//	�ˌ����̉��F
const DirectX::SimpleMath::Color	  TackleEnemy::TACKLE_PREDICTION_YELLOW = DirectX::SimpleMath::Color(0.8f, 0.7f, 0.0f, 1.0f);
//	�ˌ����̐ԐF
const DirectX::SimpleMath::Color	  TackleEnemy::TACKLE_PREDICTION_RED	= DirectX::SimpleMath::Color(0.7f, 0.0f, 0.0f, 1.0f);


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="position">���W</param>
/// <param name="helath">�̗�</param>
/// <param name="power">��</param>
/// <param name="level">���x��</param>
/// <param name="obj">�I�u�W�F�N�g�̃^�C�v</param>
TackleEnemy::TackleEnemy(const DirectX::SimpleMath::Vector3& position, int helath, const int& power, int level, ObjectType obj)
	:Enemy(position, helath, power, TACKLE_EXP ),
	m_level(level),
	m_objType(obj),
	m_isTackle(false),
	m_tackleExcute(false),
	m_tackleCoolTime(false),
	m_tackleInterval(0.0f),
	m_tackleAssaultTime(0.0f),
	m_tackledStayTime(0.0f),
	m_swoonTime(0.0f),
	m_shadowScale(1.2f),
	m_tackleState(TackleState::IDLE)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
TackleEnemy::~TackleEnemy()
{
}

/// <summary>
/// ����������
/// </summary>
void TackleEnemy::Initialize()
{
	//	���f�����擾
	m_enemyModel = MyLib::ResourcesData::GetInstance()->GatModel(L"enemy_tackle");
	//	�ʏ�̑傫����
	SetScale(DEFAULT_SCALE);
	//	�����蔻��̒ǉ�
	AddColisionEnemy
	(
		SPERE_COLLISION,
		SEARCH_COLLISION,
		TACKLE_COLLISION
	);

	//	�ŏ���-z�����ʂɌ�������
	SetRotate(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, GetAngle()));	
	//	�ˌ��͈͗p
	m_primitiveBox = DirectX::GeometricPrimitive::CreateBox(MyLib::ScreenResources::GetInstance()->GetDeviceContext(), DirectX::SimpleMath::Vector3(0.5f, 0.008f, 1.0f));
	//	���ʎq��ݒ肷��
	SetType(m_objType);
	//	���N���X�̏�����
	Enemy::Initialize();
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void TackleEnemy::Update(const DX::StepTimer& timer)
{
	using namespace DirectX::SimpleMath;

	//	�����Ă��邩
	IsAlive();

	//	�n�ʂɖ�����Ȃ��悤��
	SetPosition(Vector3(GetPosition().x, 0.0f, GetPosition().z));
	//	���S�A�j���[�V�������Ȃ珈�����s��Ȃ�
	if (IsDeadAnimation())	return;
	//	�X�^��
	if(Swoon(timer))		return;
	//	�ǔ���Ԃɓ���܂ō��G���[�h�ɂ���
	if (!IsHate())
	{
		//	�G�������ړ�������
		AutoMove(timer, ENEMY_SPEED, LOOK_BACK_SPEED);
	}
	else
	{
		//	�v���C���[��ǔ�
		HateMode(timer);
	}
	//	���N���X���X�V����
	Enemy::Update(timer);
}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="view">�r���[</param>
/// <param name="proj">�v���W�F�N�V����</param>
void TackleEnemy::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	auto screen = MyLib::ScreenResources::GetInstance();

	//	�ˌ��̗\������`��
	ComingTackle(view, proj); 
	//	�ۉe�����
	CreateShadow(view, proj, m_shadowScale);
	// �X�P�[���s��
	DirectX::SimpleMath::Matrix scale = DirectX::SimpleMath::Matrix::CreateScale(GetScale() + m_tackleScale);
	// �ʒu�s��
	DirectX::SimpleMath::Matrix trans = DirectX::SimpleMath::Matrix::CreateTranslation(GetPosition());
	// ��]�s��
	DirectX::SimpleMath::Matrix rotate = DirectX::SimpleMath::Matrix::CreateFromQuaternion(GetRotate() * m_swoonRotate);
	// ���[���h�ϊ��s��ɕϊ��i�X�P�[���A��]�A�ʒu�̏��œK�p�j
	DirectX::SimpleMath::Matrix world	= scale * rotate * trans;

	// �G�����G��Ԃ܂��͎��S�A�j���[�V�������̏ꍇ�A���C���[�t���[���̕`����s��
	if (IsDeadAnimation())
	{
		m_enemyModel->Draw(screen->GetDeviceContext(), *screen->GetCommonState(), world, view, proj, true);
	}
	else
	{
		// �ʏ�̕`����s��
		m_enemyModel->Draw(screen->GetDeviceContext(), *screen->GetCommonState(), world, view, proj);
	}
}

/// <summary>
/// �I������
/// </summary>
void TackleEnemy::Finalize()
{
}

/// <summary>
/// �v���C���[�q�b�g
/// </summary>
/// <param name="direction"></param>
/// <param name="nockBack"></param>
void TackleEnemy::HitPlayer(const DirectX::SimpleMath::Vector3& direction, const float& nockBack)
{
	DirectX::SimpleMath::Vector3 vel = direction * nockBack;
	//	�ړ��ʂ𑫂�
	SetPosition(GetPosition() + vel);
	//	�q�b�g�͂��Ă���̂œˌ���Ԃ��I����
	m_tackleState = TackleState::FINISHED;
}

/// <summary>
/// �����Ă��邩�H
/// </summary>
void TackleEnemy::IsAlive()
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
	m_tackleScale = DirectX::SimpleMath::Vector3::Zero;

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
void TackleEnemy::HateMode(const DX::StepTimer& timer)
{
	using namespace DirectX::SimpleMath;

	Vector3 vel = Vector3::Zero;

	switch (m_tackleState)
	{
	// �^�b�N�����J�n����Ă��Ȃ��ꍇ�̏���
	case TackleState::IDLE:
	{
		if (InAbility() && !m_tackleExcute)
		{
			m_tackleExcute = true;
			//	�v���C���[������悤�ɂ���
			m_objectiveRotate = GetObjectiveRotate();
			//	�ڕW���W��ݒ肷��
			m_objectivePosition = GetTargetPosition() - Vector3::Transform(Vector3(0.0f, 0.0f, 3.5f), m_objectiveRotate);
		}
		//	�ˌ��͈͓��ɂ���Ȃ�
		if (m_tackleExcute)
		{			
			//	�ˌ����̑傫��
			m_tackleScale -= DirectX::SimpleMath::Vector3(0.002f, 0.002f, 0.002f);

			SetRotate(Quaternion::Lerp(GetRotate(), m_objectiveRotate, LOOK_BACK_SPEED));
			//	�o�ߎ��Ԃ𑫂�
			m_tackleInterval += static_cast<float>(timer.GetElapsedSeconds());

			//	�ˌ������ɓ����Ďw�莞�Ԃ��Ɠˌ��Ɉڍs����
			if (m_tackleInterval >= TACKLE_ENABLED_TIME)
			{
				m_tackleState = TackleState::ACTIVE;
			}

			return;
		}
		//	�������擾����
		Vector3 dir = GetTargetPosition() - GetPosition();
		//	���ꂷ������ǔ��𔲂���
		if (dir.Length() >= TACKLE_DISTANCE)
		{
			SetHate(false);
		}

		//	�v���C���[������悤�ɂ���
		SetRotate(Quaternion::Lerp(GetRotate(), GetObjectiveRotate(), LOOK_BACK_SPEED));
		// �L�����N�^�[�̈ʒu����ڕW�ʒu�ւ̃x�N�g�����v�Z
		Vector3 direction = GetTargetPosition() - GetPosition();
		// �x�N�g���𐳋K�����đ��x��������
		direction.Normalize();
		vel = direction * ENEMY_SPEED;
		//	�ړ��ʂ𑫂�
		SetPosition(GetPosition() + vel);

		break;
	}
	// �ˌ����̋���
	case TackleState::ACTIVE:
	{		
		//	�ˌ��O�ɏ�����
		if (!m_isTackle)
		{
			PreTackleInitialize();
		}
		//	�i�X�Ɩ߂�
		m_tackleScale = DirectX::SimpleMath::Vector3::Lerp(m_tackleScale, DirectX::SimpleMath::Vector3::Zero, 0.1f);
		//	�o�ߎ��Ԃ𑫂�
		m_tackleAssaultTime += static_cast<float>(timer.GetElapsedSeconds());
		// �^�b�N�����I�����ׂ��������`�F�b�N
		if (ShouldStopTackle() || m_tackleAssaultTime >= 1.2f)
		{
			// �^�b�N�����I��
			m_tackleState = TackleState::FINISHED;
		}

		// �^�b�N�����̋���
		vel = StartTackle(m_objectivePosition, ENEMY_TACLE_SPEED);
		//	�ړ��ʂ𑫂�
		SetPosition(GetPosition() + vel);

		break;
	}
	// �^�b�N�����I�������ꍇ�̋���
	case TackleState::FINISHED:
	{	
		//	�ˌ��͏I��
		m_isTackle = false;
		//	�o�ߎ��Ԃ𑫂�
		m_tackledStayTime += static_cast<float>(timer.GetElapsedSeconds());
		//	�������̏�ɂƂǂ܂�
		if (m_tackledStayTime >= ALIVE_TIME)
		{
			//	�l������������
			m_tackleInterval = 0.0f;
			m_tackleAssaultTime = 0.0f;
			m_tackledStayTime = 0.0f;
			m_swoonTime = 0.0f;
			m_tackleExcute = false;
			m_tackleState = TackleState::IDLE;
			m_tackleScale = DirectX::SimpleMath::Vector3::Zero;
		}

		break;
	}
	default:	break;
	}
}

/// <summary>
/// �^�b�N���̏I������
/// </summary>
/// <returns></returns>
bool TackleEnemy::ShouldStopTackle()
{
	// �^�b�N�����I�����ׂ��������`�F�b�N
	if ((m_objectivePosition - GetPosition()).Length() <= TACKLE_STOP_DISTANCE && m_isTackle)
	{
		return true;
	}
	
	return false;
}

/// <summary>
/// �X�^�����
/// </summary>
/// <param name="timer">�^�C�}�[</param>
/// <returns></returns>
bool TackleEnemy::Swoon(const DX::StepTimer& timer)
{
	//	�ˌ���ԂȂ�
	if (m_tackleState == TackleState::SWOON)
	{
		//	�G����
		m_swoonRotate *= DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(5.0f));
		//	���Ԃ𑫂�
		m_swoonTime += static_cast<float>(timer.GetElapsedSeconds());
		//	���N���X���X�V����
		Enemy::Update(timer);
		//	�X�^����Ԃ̔����ʂ܂ł͌��ɉ�����
		if (m_swoonTime < SWOON_TIME / 1.5f)
		{
			//	���ɉ�����
			DirectX::SimpleMath::Vector3 BackSpeed = DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(0.0f, 0.0f, ENEMY_SPEED), GetRotate());
			SetPosition(GetPosition() + BackSpeed);
		}
		//	�X�^�����
		if (m_swoonTime > SWOON_TIME)
		{
			m_tackleState = TackleState::FINISHED;
		}

		return true;
	}
	else
	{
		m_swoonRotate = DirectX::SimpleMath::Quaternion::Identity;
	}

	return false;
}

/// <summary>
/// �ˌ��͈͂������Ă�����
/// </summary>
/// <param name="view">�r���[</param>
/// <param name="proj">�v���W�F�N�V����</param>
void TackleEnemy::ComingTackle(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	using namespace DirectX::SimpleMath;

	//	�ˌ��͈͂ɓ�������`�� || ���S�A�j���[�V�������͕`�悵�Ȃ� || �ǔ����[�h�͕`�悵�Ȃ�
	if (IsDeadAnimation() || !IsHate())	return;
	//	�`�掞��
	float renderTime = TACKLE_ENABLED_TIME / 5.0f;

	//	�������u�ԕ`��͕ςȂ̂ŏ����o������ && ��Ԃ��ҋ@��ԂȂ�
	if (m_tackleInterval >= renderTime && m_tackleState == TackleState::IDLE)
	{
		// �^�b�N�����̋���
		Matrix world = DirectX::SimpleMath::Matrix::CreateScale(m_tackleInterval * 3.4f, 1.f, 8.0f) * Matrix::CreateTranslation(0.0f, 0.0f, -4.0f) *(Matrix::CreateFromQuaternion(GetRotate())) * Matrix::CreateTranslation(GetPosition());

		//	�ˌ��ԍۂɂȂ�ΐF��ς���
		if (m_tackleInterval >= TACKLE_ENABLED_TIME - 0.24f)
		{
			//	�\�����̕`��
			m_primitiveBox->Draw(world, view, proj, TACKLE_PREDICTION_RED);
		}
		else
		{
			//	�\�����̕`��
			m_primitiveBox->Draw(world, view, proj, TACKLE_PREDICTION_YELLOW);
		}
	}
}

/// <summary>
/// �w�肳�ꂽ���x�ł��Ă���
/// </summary>
/// <param name="position">�ڕW���W</param>
/// <param name="speed">���x</param>
/// <returns>�ړ���</returns>
DirectX::SimpleMath::Vector3 TackleEnemy::StartTackle(const DirectX::SimpleMath::Vector3& position, const float& speed)
{
	// �L�����N�^�[�̈ʒu����ڕW�ʒu�ւ̃x�N�g�����v�Z
	DirectX::SimpleMath::Vector3 direction = position - GetPosition();

	// �x�N�g���𐳋K�����đ��x��������
	direction.Normalize();
	return  direction * speed;
}

/// <summary>
/// �X�^����Ԃɂ���
/// </summary>
void TackleEnemy::SwoonMode()
{
	m_tackleState = TackleState::SWOON;
}

/// <summary>
/// �ˌ��̍ۂ̏���������
/// </summary>
void TackleEnemy::PreTackleInitialize()
{
	m_isTackle = true;
}