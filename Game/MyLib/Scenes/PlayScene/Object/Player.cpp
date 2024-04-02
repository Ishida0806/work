//
//		File Name �F Player.cpp
//		Production�F 2023/6/12
//		Author�@�@�F �Γc ����	
// 
//		�v���C���[�̊Ǘ��N���X
//	
#include "pch.h"
#include "Player.h"
#include "PlayeComponent/PlayerPartsFactory.h"
#include "../PlayScene.h"


//	�Փˎ��̃m�b�N�o�b�N	
const float Player::REACTION									 = 0.9f;
//	�ǂ̏ꏊ	
const float Player::WALL_PLACE									 = 23.5f;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="playerParam">�v���C���[�p�����[�^</param>
Player::Player(PlayerData* playerParam)
	:
	m_playerParam(playerParam),
	Object(playerParam->position),
	PlayerStatus(this, playerParam->playerHealth),
	PlayerMove(this),
	m_animationTime(0.0f),
	m_gravity(0.0f),
	m_isAlive(false),
	m_isDeathAnimation(false),
	m_isWinAnimation(false),
	m_isAnimation(false)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Player::~Player()
{
	Finalize();
}

/// <summary>
/// ������
/// </summary>
void Player::Initialize()
{
	CreateDeviceDependentResources();
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void Player::Update(const DX::StepTimer& timer)
{
	//	���S�A�j���[�V�������Ȃ�A��
	if (m_isAnimation || m_isAlive)	return;
	//	�v���C���[�X�e�[�^�X�̍X�V
	PlayerStatus::Update(timer);
	//�@�v���C���[�𓮂���
	PlayerMove::MovePlayer();
	//	�����蔻��̍X�V
	UpdateColison();
	//	�J�[�\���X�V
	m_cursol->Update(timer);
	//	�J�[�\���̍��W���X�V
	m_cursorPosition = m_cursol->GetPosition();
	// �v���C���[�ƌ��̍X�V
	UpdatePlayerAndSordLerp();	
	//	���̍X�V
	m_sord->Update(timer);
	//	�v���C���[�T�[�N�����X�V����
	m_playerArrow->Update(timer);
	//	�v���C���[���X�e�[�W�ɗ��܂点��
	ArriveStage();
	//	�v���C���[�p�[�c�̍X�V
	for (const auto& parts : m_playerParts)	parts->UpdateParts(timer);
}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="view">�r���[</param>
/// <param name="proj">�v���W�F�N�V����</param>
void Player::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	//	�e�����
	DirectX::SimpleMath::Matrix shadowWorld = DirectX::SimpleMath::Matrix::CreateScale(1.5f, 0.01f, 1.5f) * DirectX::SimpleMath::Matrix::CreateTranslation(GetPosition().x, 0.01f, GetPosition().z);
	//	�e��`�悷��
	m_primitive->Draw
	(
		shadowWorld,
		view,
		proj,
		DirectX::Colors::Black
	);
	//	�ړ��s��
	DirectX::SimpleMath::Matrix trans  = DirectX::SimpleMath::Matrix::CreateTranslation(GetPosition());
	//	��]�s��
	DirectX::SimpleMath::Matrix rotate = DirectX::SimpleMath::Matrix::CreateFromQuaternion(GetRotate());
	//	�g��s��
	DirectX::SimpleMath::Matrix scale  = DirectX::SimpleMath::Matrix::CreateScale(GetScale());
	//	���[���h
	DirectX::SimpleMath::Matrix world  = scale * rotate * trans;
	//	�����A�j���[�V�������͕`�悵�Ȃ�
	if (!m_isWinAnimation) 
	{ 
		//	�J�[�\���̕`��
		m_cursol->Render(view, proj);
		//	���̕`��
		m_sord->Render(view, proj); 
		//	�v���C���[�T�[�N����`��
		m_playerArrow->Render(view, proj);
	}
	//	���f���̕`��
	for (const auto& parts : m_playerParts)	parts->DrawModel(nullptr, world, view, proj);	
}

/// <summary>
///	�I������
/// </summary>
void Player::Finalize()
{
	m_cursol->Finalize();
	m_sord->Finalize();
}

/// <summary>
/// �_���[�W�𔽉f
/// </summary>
/// <param name="damege">�_���[�W</param>
void Player::Damege(const int& damege)
{
	//	���G�^�C������Ȃ��Ȃ�A��
	if (IsInvincible())	return;
	//	�̗͂����炷
	SetDamege(damege);
}

/// <summary>
/// �_���[�W��^����
/// </summary>
/// <param name="damege">�_���[�W</param>
/// <param name="direction">�ǂ̋����ɂ���Ă邩</param>
void Player::Damege(const int& damege, DirectX::SimpleMath::Vector3 direction, float reaction)
{
	//	���G�^�C������Ȃ��Ȃ�A��
	if (IsInvincible())	return;
	//	�̗͂����炷
	SetDamege(damege);
	//	�m�b�N�o�b�N��^����
	DirectX::SimpleMath::Vector3 vel = direction * reaction;
	//	����������
	vel.y += 0.5f;
	//	���W�ɉ��Z
	SetVelocity(vel);
}

/// <summary>
/// �_���[�W��^����
/// </summary>
/// <param name="damege">�_���[�W��</param>
/// <param name="direction">����</param>
/// <param name="reaction">�ӂ��Ƃ΂���</param>
void Player::Damege(const int& damege, DirectX::SimpleMath::Vector3 direction, const DirectX::SimpleMath::Vector3& reaction)
{
	//	���G�^�C������Ȃ��Ȃ�A��
	if (IsInvincible())	return;
	//	�̗͂����炷
	SetDamege(damege);
	//	�m�b�N�o�b�N��^����
	DirectX::SimpleMath::Vector3 vel = direction * reaction;
	//	������
	vel.y += 1.0f;
	//	���W�ɉ��Z
	SetVelocity(vel);
}

/// <summary>
/// ���S���̃A�j���[�V����
/// </summary>
/// <param name="timer">�^�C�}�[</param>
/// <param name="flag">�t���O</param>
void Player::DethAnimation(const DX::StepTimer& timer)
{
	using namespace DirectX::SimpleMath;

	if (!m_isDeathAnimation)	return;

	//	�o�ߎ��Ԃ𑫂�
	m_animationTime += static_cast<float>(timer.GetElapsedSeconds());

	if (m_isDeathAnimation)
	{
		for (const auto& parts : m_playerParts)	parts->DeathAnimation(timer);
		//	�\�[�h���S�A�j���[�V����
		m_sord->SordDeathAniamtion();
	}
	//	���S�A�j���[�V�������Ԃ��I�������m���ɎE��
	if (m_animationTime >= m_playerParam->deathAnimationTime)
	{
		m_isAnimation	   = false;
		m_isAlive		   = true;
	}
}

/// <summary>
/// �������̃A�j���[�V����
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void Player::WinAnimation(const DX::StepTimer& timer)
{
	using namespace DirectX::SimpleMath;

	if (!m_isWinAnimation)	return;

	//	�o�ߎ��Ԃ𑫂�
	m_animationTime += static_cast<float>(timer.GetElapsedSeconds());

	if (m_isWinAnimation)
	{
		for (const auto& parts : m_playerParts) 
		{ 
			parts->WinAnimation(timer);
		}
	}
	//	�����A�j���[�V�������Ԃ��I�������t���O��ς���
	if (m_animationTime >= m_playerParam->winAnimationTime)
	{
		m_isAnimation = false;
	}
}


/// <summary>
/// �e�I�u�W�F�N�g���̍쐬
/// </summary>
void Player::CreateDeviceDependentResources()
{
	//	�v���C���[���f�����擾
	m_playerModel = MyLib::ResourcesData::GetInstance()->GatModel(L"playerHead");
	//	�J�[�\�����쐬����
	m_cursol = std::make_unique<Cursor>(GetPosition(), m_cursorRotate, GetAngle());
	m_cursol->Initialize();
	//	�����쐬����
	m_sord = std::make_unique<Sord>(this);
	m_sord->Initialize();

	//	�v���C���[�T�[�N��
	m_playerArrow = std::make_unique<PlayerArrow>(
		this,
		MyLib::ResourcesData::GetInstance()->GatModel(L"arrow"),
		&m_cursorPosition,
		&m_cursorRotate
	);
	//	�T�[�N���̏�����
	m_playerArrow->Initialize();
	//	���̔��a
	m_playerSphere.radius = 0.8f;
	//	���̐^��
	m_playerSphere.center = GetPosition();
	//�@�v���~�e�B�u�o�b�`�̏�����
	m_primitive = DirectX::GeometricPrimitive::CreateSphere(MyLib::ScreenResources::GetInstance()->GetDeviceContext(), 1.0f);
	//	���ʎq��o�^����
	SetType(ObjectType::Player);
	//	�����蔻���ǉ�����
	AddColision(&m_playerSphere, Object::ColisionType::NormalColision);
	//	�傫����ݒ肷��
	SetScale(m_playerParam->modelScale);
	//	�v�f�̒ǉ�
	m_playerParts.push_back(PlayerPartsFactory::CreatePlayerBody(this, this));
	//	�v���C���[�X�e�[�^�X�̏�����
	PlayerStatus::Initialize();
}

/// <summary>
/// �����Ă��邩�m�F����
/// </summary>
/// <returns>���S���</returns>
bool Player::HealthCheck()
{
	//	�̗͂�0���傫���Ȃ�A��
	if (GetHealth() > 0) return false;
	//	�̗͂�0��
	HealthZero();
	//	���S����
	return true;
}

/// <summary>
/// �v���C���[���X�e�[�W�ɗ��܂点��
/// </summary>
void Player::ArriveStage()
{
	//	�v���C���[�̈ʒu�𐧌䂷��
	float x = Utility::Clamp(GetPosition().x, -WALL_PLACE, WALL_PLACE);
	float y = Utility::Clamp(GetPosition().y,  0.0f		 , 50.0f);
	float z = Utility::Clamp(GetPosition().z, -WALL_PLACE, WALL_PLACE);
	//	�d��
	if (y > 0.0f) { m_gravity -= m_playerParam->gravity; }	else  { m_gravity = 0.0f; }
	//	�d��
	y += m_gravity;
	//	�N�����v�̐������
	SetPosition(DirectX::SimpleMath::Vector3(x, y, z));
}

/// <summary>
///  �v���C���[�̃A�j���[�V����
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void Player::PlayerAnimation(const DX::StepTimer& timer)
{
	//	���S�A�j���[�V����
	if (m_isDeathAnimation) { DethAnimation(timer);}
	//	�����A�j���[�V����
	if (m_isWinAnimation)	{ WinAnimation(timer); }
}

/// <summary>
/// �������ʂɂ���ăA�j���[�V������������
/// </summary>
/// <param name="resultString">��������</param>
void Player::WhyGameResult(const std::string& resultString)
{
	//	����
	if (resultString == PlayScene::WIN_STRING)
	{
		m_isWinAnimation = true;
		//	�A�j���[�V�������J�n����
		m_isAnimation = true;
		//	�|���̂ŏ�����
		SetRotate(DirectX::SimpleMath::Quaternion::Identity);
		//	���ʂ�����
		SetRotate(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY,DirectX::XMConvertToRadians(180.0f)));
	}
	//	����
	else if(resultString == PlayScene::LOSE_STRING)
	{
		m_isDeathAnimation = true;
		//	�A�j���[�V�������J�n����
		m_isAnimation = true;
	}
}

/// <summary>
///	�R���W�����̍X�V
/// </summary>
void Player::UpdateColison()
{
	DirectX::SimpleMath::Vector3 posCenter = GetPosition();
	posCenter.y += 1.0f;
	m_playerSphere.center = posCenter;
}

/// <summary>
/// �v���C���[�ƌ��̍X�V
/// </summary>
void Player::UpdatePlayerAndSordLerp()
{
	//	�������Z�o����
	DirectX::SimpleMath::Vector3 dir = m_cursol->GetPosition() - GetPosition();
	//	�����Ă�������Ɍ���
	m_cursorRotate = DirectX::SimpleMath::Quaternion::FromToRotation(DirectX::SimpleMath::Vector3::Forward, dir);
	//	�U�����Ȃ烉�[�v���s��Ȃ�
	if (m_sord->IsAttack())	return;
	//	���[�v������
	SetRotate(DirectX::SimpleMath::Quaternion::Lerp(GetRotate(), m_cursorRotate, m_playerParam->turnSpeed));
}