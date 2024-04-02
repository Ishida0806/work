//
//		File Name �F Bullet.cpp
//		Production�F 2023/7/02
//		Author�@�@�F �Γc ����
// 
//		�e�̎������s�����N���X
//
#include "pch.h"
#include "Bullet.h"

//	�i�s���x
const float						   Bullet::SPEED			= 0.22f;
//	�G�e�̑��x
const DirectX::SimpleMath::Vector3 Bullet::ENEMY_SPEED		= DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.1f);
//	�{�X�e�̑��x
const DirectX::SimpleMath::Vector3 Bullet::BOSS_SPEED		= DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.15f);
//	���˂��ꂽ�ۂ̐i�ޑ��x
const DirectX::SimpleMath::Vector3 Bullet::REF_SPEED		= DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.25f);
//	�G�̒e�̂����蔻��̑傫��
const float Bullet::BULLET_RADIUS							= 0.4f;
//	�{�X�̒e�̂����蔻��̑傫��
const float Bullet::BOSS_BULLET_RADIUS						= 0.5f;


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="ownerID">�I�[�i�[</param>
/// <param name="position">���W</param>
/// <param name="rotate">��]�p</param>
/// <param name="color">�F</param>
/// <param name="power">��</param>
/// <param name="scale">�傫��</param>
/// <param name="used">�g�p���</param>
Bullet::Bullet(BulletFactory::OwnerID ownerID, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& rotate, const DirectX::SimpleMath::Color& color, int power, float scale, bool used)
	:
	Object(position, rotate),
	m_ownerID(static_cast<int>(ownerID)),
	m_color(color),
	m_power(power),
	m_scale(scale),
	m_used(used),
	m_refCount(0),
	m_primitive{},
	m_isRefrect(false)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Bullet::~Bullet()
{
}

/// <summary>
/// ����������
/// </summary>
void Bullet::Initialize()
{
	CreateDeviceDependentResources();
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void Bullet::Update(const DX::StepTimer& timer)
{
	using namespace DirectX;
	timer;
	SetVelocity(m_velocity);
	//	�ړ����� 
	SetVelocity(ShotBullet());
	//	Y�����Œ肳����	
	SimpleMath::Vector3 position = GetPosition();
	position.y = 0.8f;
	SetPosition(position);
	//	�e�̓����蔻��ɑ������
	position.y = 0.5f;
	m_bulletSphere.center = position;
}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="view">�r���[</param>
/// <param name="proj">�v���W�F�N�V����</param>
void Bullet::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	//	�e���ړ�
	DirectX::SimpleMath::Matrix scale = DirectX::SimpleMath::Matrix::CreateScale(m_scale);
	DirectX::SimpleMath::Matrix trans = DirectX::SimpleMath::Matrix::CreateTranslation(GetPosition());
	//	���̃��[���h
	DirectX::SimpleMath::Matrix world = scale * trans;
	//	���ˏ�Ԃɂ���ĕ`���ς���
	if (m_isRefrect)
	{
		//	�v���~�e�B�u�o�b�`�̕`��
		m_primitive->Draw(world, view, proj, DirectX::Colors::White);
	}
	else
	{
		m_primitive->Draw(world, view, proj, m_color);
	}

	//	�e�����
	scale = DirectX::SimpleMath::Matrix::CreateScale(0.3f, 0.01f, 0.3f);
	trans = DirectX::SimpleMath::Matrix::CreateTranslation(GetPosition().x, 0.0f, GetPosition().z);
	//	�V���h�[�s��̍쐬
	DirectX::SimpleMath::Matrix shadowWorld = scale * trans;
	//	���f���̕`����s��
	m_primitive->Draw(shadowWorld, view, proj, DirectX::SimpleMath::Color(0.0f, 0.0f, 0.0f, 1.0f));	
}

/// <summary>
/// �I������
/// </summary>
void Bullet::Finalize()
{

}

/// <summary>
/// �Ďg�p���̏���������
/// </summary>
void Bullet::PreInitialize()
{
	m_isRefrect = false;
	//m_refCount  = 3;
	m_velocity  = DirectX::SimpleMath::Vector3::Zero;
}

/// <summary>
/// �f�o�C�X�ˑ��̏�����
/// </summary>
void Bullet::CreateDeviceDependentResources()
{
	//�@�v���~�e�B�u�o�b�`�̏�����
	m_primitive = DirectX::GeometricPrimitive::CreateSphere(MyLib::ScreenResources::GetInstance()->GetDeviceContext(), 1.0f);
	
	//	������ɂ���ē����蔻���ς���
	if(m_ownerID == static_cast<int>(BulletFactory::OwnerID::ENEMY))		m_bulletSphere.radius = BULLET_RADIUS;
	if(m_ownerID == static_cast<int>(BulletFactory::OwnerID::BOSS))			m_bulletSphere.radius = BOSS_BULLET_RADIUS;
}

/// <summary>
/// �e���X�V����
/// </summary>
/// <returns>VELOCITY</returns>
DirectX::SimpleMath::Vector3 Bullet::ShotBullet()
{
	using namespace DirectX::SimpleMath;

	//	���ˏ�ԂȂ�A��
	if (m_isRefrect)	return Vector3::Zero;
	//	�G�̃I�[�i�[
	BulletFactory::OwnerID Owner = static_cast<BulletFactory::OwnerID>(m_ownerID);

	//	���L�҂ɂ���Ēe�̑��x��ς���
	switch (Owner)
	{
	//	���L�҂��G�̏ꍇ
	case BulletFactory::OwnerID::ENEMY:	return Vector3::Transform(ENEMY_SPEED, GetRotate());	break;
	//	���L�҂��G�̏ꍇ
	case BulletFactory::OwnerID::BOSS:	return Vector3::Transform(BOSS_SPEED,  GetRotate());	break;
	//	����ȊO�͋A��
	default:							return Vector3::Zero;									break;
	}
}

/// <summary>
/// �g�p��Ԃ�ݒ肷��
/// </summary>
/// <param name="used">�g�p���</param>
void Bullet::SetUsed(bool used)
{
	m_used = used;
	//	�g�p��ԂɈڍs������l��������
	if (m_used) { PreInitialize(); }
}

/// <summary>
/// ���˂��s��
/// </summary>
/// <param name="position">���W</param>
void Bullet::Refrection(const DirectX::SimpleMath::Vector3& position)
{
	//	�������Z�o����
	DirectX::SimpleMath::Vector3 direction = GetPosition() - position;
	direction.y = 0.0f;
	direction.Normalize();
	//	���ˊp�Ɍ������Đi��
	if (!m_isRefrect) { m_velocity = direction * SPEED; } else { m_velocity = direction * (SPEED * 1.5f); }

	//	���ˏ�Ԃ�
	m_isRefrect = true;	
}