//
//		File Name �F BulletManager.cpp
//		Production�F 2023/7/02
//		Author�@�@�F �Γc ����
// 
//		�e�̔��ˁE�z����Ǘ�����
//
#include "pch.h"
#include "BulletManager.h"

#include "Game/MyLib/Scenes/PlayScene/Object/Bullet/Bullet.h"
#include "Game/MyLib/Scenes/PlayScene/Object/Bullet/BulletFactroy.h"
#include "Game/MyLib/Scenes/PlayScene/Object/Enemy/Enemy.h"
#include "Game/MyLib/Scenes/PlayScene/PlayScene.h"

//	�G�̒e�̍U����
const int BulletManager::ENEMY_BULLET_POWER   = 3;
//	�{�X�̒e�̍U����
const int BulletManager::BOSS_BULLET_POWER	  = 9;
//	�{�X�e�̑傫��
const float BulletManager::BOSS_BULLET_SCLAE  = 0.7f;
//	�ʏ�G�̒e�̑傫��
const float BulletManager::ENEMY_BULLET_SCLAE = 0.6f;


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="enemy">�G����</param>
BulletManager::BulletManager(std::vector<std::shared_ptr<Enemy>>& enemy)
	:m_enemys(enemy)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BulletManager::~BulletManager()
{
}

/// <summary>
/// ����������
/// </summary>
void BulletManager::Initialize()
{
	//	�{�X�̓G�̒e���쐬����
	for (int index = 0; index < BossEnemy::BOSS_BULLETS_NUM; ++index)
	{
		//	�G�̒e���쐬����
		m_bullets.push_back
		(
			BulletFactory::CreateBullets
			(
				BulletFactory::OwnerID::BOSS,
				DirectX::SimpleMath::Vector3::Zero,
				DirectX::SimpleMath::Quaternion::Identity,
				BulletFactory::BOSS_BULLETS_COLOR,
				BOSS_BULLET_POWER,
				BOSS_BULLET_SCLAE,
				false
			)
		);
	}
	//	�ʏ�G�̒e���쐬����
	for (int index = 0; index < NormalEnemy::ENEMY_BULLETS_NUM; ++index)
	{
		//	�G�̋����쐬����
		m_bullets.push_back
		(
			BulletFactory::CreateBullets
			(
				BulletFactory::OwnerID::ENEMY,
				DirectX::SimpleMath::Vector3::Zero,
				DirectX::SimpleMath::Quaternion::Identity,
				BulletFactory::ENEMY_BULLETS_COLOR,
				ENEMY_BULLET_POWER,
				ENEMY_BULLET_SCLAE,
				false
			)
		);
	}
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void BulletManager::Update(const DX::StepTimer& timer)
{
	// �ʏ�̒e�𔭎˂���
	ShotBossBullets();
	// �{�X�̒e�𔭎˂���
	ShotEnemyBullets();
	// �ʏ�̒e���X�V����
	UpdateNormalBullet(timer);
}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="view">�r���[</param>
/// <param name="proj">�v���W�F�N�V����</param>
void BulletManager::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	//	�G�̒e�����X�V����
	for (const auto& enemybullet : m_bullets)
	{
		//	�C�e���g�p����
		if (!enemybullet->IsUsed()) continue;

		//	�`�悷��
		enemybullet->Render(view, proj);
	}
}

/// <summary>
/// �ʏ�̒e���X�V�X�V����
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void BulletManager::UpdateNormalBullet(const DX::StepTimer& timer)
{
	for (const auto& enemybullet : m_bullets)
	{
		if (!enemybullet->IsUsed()) continue;

		// �X�V����
		enemybullet->Update(timer);
	}
}

/// <summary>
/// �G�̒e�𔭎˂���
/// </summary>
void BulletManager::ShotEnemyBullets()
{
	for (const auto& enemy : m_enemys)
	{
		//	�ʏ�̓G�ȊO�͋A��
		if (enemy->GetType() != Object::ObjectType::NormalEnemy)	continue;
		//	���ˉ\���H
		if (!enemy->IsRedyAbility()) continue;

		for (const auto& bullet : m_bullets)
		{
			//	�G�̃I�[�i�[���擾����
			BulletFactory::OwnerID Owner = static_cast<BulletFactory::OwnerID>(bullet->GetOwner());
			//	�{�X�̒e�ȊO�͋A��
			if (Owner != BulletFactory::OwnerID::ENEMY) continue;
			// �C�e���g�p�����ǂ����𒲂ׂ�
			if (bullet->IsUsed())	continue;
			//	�C�e���e������
			bullet->SetUsed(true);
			//	�C�e�����˂����ʒu���v�Z���� 
			DirectX::SimpleMath::Vector3 offsetPos = DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(0.0f, 0.0f, 1.f), enemy->GetRotate());
			//	���ˈʒu��ݒ肷��
			bullet->SetPosition(enemy->GetPosition() - offsetPos);
			//	�p�x������Ă邽�ߕ␳
			DirectX::SimpleMath::Quaternion rotate = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(180.0f)) * enemy->GetRotate();
			//  ���ˊp��ݒ肷��
			bullet->SetRotate(rotate);
			//	�����I�������t���O��؂�
			enemy->SetAbility(false);
			//	SE���Đ�����
			AudioManager::GetInstance()->PlaySoundEffectSE(L"SHOT_BULLET_SE01");
			break;
		}
	}
}

/// <summary>
/// �{�X�̒e�𔭎˂���
/// </summary>
void BulletManager::ShotBossBullets()
{
	for (const auto& enemy : m_enemys)
	{
		//	�{�X�G�ȊO�͋A��
		if (enemy->GetType() != Object::ObjectType::BossEnemy)	continue;
		//	���ˉ\���H
		if (!enemy->IsRedyAbility()) continue;

		for (const auto& bullet : m_bullets)
		{
			//	�G�̃I�[�i�[���擾����
			BulletFactory::OwnerID Owner = static_cast<BulletFactory::OwnerID>(bullet->GetOwner());
			//	�{�X�̒e�ȊO�͋A��
			if (Owner == BulletFactory::OwnerID::ENEMY) continue;
			// �C�e���g�p�����ǂ����𒲂ׂ�
			if (bullet->IsUsed())	continue;
			//	�C�e���e������
			bullet->SetUsed(true);
			//	�p�x������Ă邽�ߕ␳
			DirectX::SimpleMath::Quaternion OffsetRotate = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(90.0f)) * enemy->GetRotate();
			//	�C�e�����˂����ʒu���v�Z���� 
			DirectX::SimpleMath::Vector3 offsetPos = DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(0.0f, 0.0f, 3.f), OffsetRotate);
			//	���ˈʒu��ݒ肷��
			bullet->SetPosition(enemy->GetPosition() + offsetPos);
			//  ���ˊp��ݒ肷��
			bullet->SetRotate(OffsetRotate);
			//	�����I�������t���O��؂�
			enemy->SetAbility(false);
			//	SE���Đ�����
			AudioManager::GetInstance()->PlaySoundEffectSE(L"SHOT_BULLET_SE02");

			break;
		}
	}
}
