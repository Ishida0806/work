
#include "pch.h"
#include "ColisionObjects.h"

#include "Game/MyLib/Scenes/PlayScene/PlayScene.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="playScene">�v���C�V�[��</param>
/// <param name="player">�v���C���[<</param>
/// <param name="enemys">�G�B</param>
/// <param name="bullets">�e</param>
/// <param name="walls">��</param>
/// <param name="items">�A�C�e��</param>
ColisionObjects::ColisionObjects(PlayScene* playScene, Player* player, std::vector<std::shared_ptr<Enemy>>* enemys, std::vector<std::unique_ptr<Bullet>>* bullets, std::vector<std::unique_ptr<Wall>>* walls, std::vector<std::shared_ptr<Item>>* items)
	:m_playScene(playScene),
	m_player(player),
	m_enemys(*enemys),
	m_bullets(*bullets),
	m_walls(*walls),
	m_items(*items)
{
}
/// <summary>
/// �������
/// </summary>
void ColisionObjects::UpdateAbility()
{
	//	�v���C���[���Z�\�͈͓��ɂ��邩
	InEnemiesAbility();
}

/// <summary>
/// �����蔻��̍X�V
/// </summary>
void ColisionObjects::UpdateColision()
{
	//	�A�C�e���̓����蔻��
	UpdateItem();
	//	�v���C���[�̓����蔻��̍X�V
	ColisionPlayer();
	//	�e�̓����蔻��̍X�V
	ColisionBullets();
	//	�G���m�̏Փ˔���
	ColisionEnemies();
	//	�G�̍��G�͈͂ɓ����ĂȂ����H
	InEnemiesSearch();
}

/// <summary>
/// �A�C�e���̓����蔻��
/// </summary>
void ColisionObjects::UpdateItem()
{
	for (const auto& item : m_items)
	{
		//	�擾�A�j���[�V�������Ȃ�A��
		if (item->IsTookAnimation())		continue;

		//	�A�C�e���ƃv���C���[�̓����蔻��
		if (Collision::CheckSphereAndSphere(item->GetSpere(), m_player->GetSphere()))
		{
			Item::ItemType itemType = item->GetItemType();

			//	�p���[�A�b�v�A�C�e��
			if (itemType == Item::ItemType::PowUp)
			{
				//	�A�C�e�����擾��Ԃ�
				item->TookItem();
				//	�p���[�A�b�v���擾����
				m_player->GetPowerUPItem();
				//	�w�肳�ꂽSE�𗬂�
				AudioManager::GetInstance()->PlaySoundEffectSE(L"PowerUP");
			}
			//	�񕜃A�C�e��
			else if (itemType == Item::ItemType::Recovery)
			{
				//	�A�C�e�����擾��Ԃ�
				item->TookItem();
				//	�񕜂��擾����
				m_player->GetRecoveryItem();
				//	�w�肳�ꂽSE�𗬂�
				AudioManager::GetInstance()->PlaySoundEffectSE(L"RecoverSE01");
			}
			//	���˃A�C�e��
			else if (itemType == Item::ItemType::Reflect)
			{
				//	�A�C�e�����擾��Ԃ�
				item->TookItem();



				//	�w�肳�ꂽSE�𗬂�
				AudioManager::GetInstance()->PlaySoundEffectSE(L"HaveWeapon");
			}
		}
	}
}

/// <summary>
/// �g�p���Ă���e�̓����蔻����X�V
/// </summary>
void ColisionObjects::ColisionBullets()
{
	//	�G�̒e
	for (const auto& enemybullet : m_bullets)
	{
		//	�v���C���[�̒e�����g�p�Ȃ珈�����s��Ȃ�
		if (!enemybullet->IsUsed()) continue;

		//	�e���ǂɂ��������疢�g�p��Ԃ�
		for (const auto& wall : m_walls)
		{
			//	�G�̒e���ǂɂ��������疢�g�p��Ԃ�
			if (Collision::CheckBoxAndSphereCollision(wall->GetWallBox(), enemybullet->GetSphere()))
			{
				//	�ǂɓ��������疢�g�p��Ԃ�
				enemybullet->SetUsed(false);
			}
		}

		//	�G
		for (const auto& enemy : m_enemys)
		{
			//	�G�����G��Ԃ����S�A�j���[�V�������Ȃ珈�����s��Ȃ�
			if (enemy->IsInvincible() || enemy->IsDeadAnimation())	continue;

			//	�v���C���[���U�����Ȃ珈�����s��
			if (Collision::CheckCapsuleAndSphere(m_player->GetSordCapuselColision(), enemy->GetSphereCollision()) && m_player->IsAttack())
			{
				//	�G�Ƀ_���[�W��^����
				enemy->Damege(m_player->GetPower());
				//	�G�t�F�N�g��`��
				m_playScene->HitRnder(enemy->GetPosition(),enemy.get());
				//	SE���Đ�����
				AudioManager::GetInstance()->PlaySoundEffectSE(L"Hit_Bullet_SE01");
			}

			//	�e�����˒����H
			if (!enemybullet->IsReslect()) continue;

			//	�G�Ɣ��ˏ�Ԃ̓G�̒e
			if (Collision::CheckSphereAndSphere(enemy->GetSphereCollision(), enemybullet->GetSphere()))
			{
				//	�G�̒e�𖢎g�p��Ԃ�
				enemybullet->SetUsed(false);

				//	�G�ɓ�����Δ��˂���
				//enemybullet->Refrection(enemy->GetPosition());
				//	�G�Ƀ_���[�W��^����
				enemy->Damege(m_player->GetPower() * 2);
				//	�G�t�F�N�g��`��
				m_playScene->HitRnder(enemy->GetPosition(), enemy.get());
				//	SE���Đ�����
				AudioManager::GetInstance()->PlaySoundEffectSE(L"Hit_Bullet_SE01");
			}
		}

		//	�v���C���[�ƓG�̒e && �e�����ˏ�Ԃ���Ȃ� && �v���C���[�����G����Ȃ��Ȃ�
		if (Collision::CheckSphereAndSphere(m_player->GetSphere(), enemybullet->GetSphere()) && !enemybullet->IsReslect() && !m_player->IsInvincible())
		{
			//	�G�̒e�𖢎g�p��Ԃ�
			enemybullet->SetUsed(false);
			//	�v���C���[�Ƀ_���[�W��^����
			m_player->Damege(enemybullet->GetPower(), Collision::HitDirectionSphereAndSphere(m_player->GetSphere(), enemybullet->GetSphere()));
			//	�G�t�F�N�g��`��
			m_playScene->HitRnder(m_player->GetPosition());
			//	SE���Đ�����
			AudioManager::GetInstance()->PlaySoundEffectSE(L"Hit_Player_SE01");
		}

		// �v���C���[���U��������Ȃ��Ȃ�A��
		if (!m_player->IsAttack()) continue;

		// ���̃J�v�Z���ƓG�̋��̔�����Ƃ� && �G�̒e�����ˏ�Ԃ���Ȃ��Ȃ�
		if (Collision::CheckCapsuleAndSphere(m_player->GetSordCapuselColision(), enemybullet->GetSphere()))
		{		
			//	���ˏ���
			enemybullet->Refrection(m_player->GetPosition());
			//	���G�ɂ��Ă�����
			m_player->SetInvincible(true);
			//	�q�b�g�G�t�F�N�g�`��
			m_playScene->HitBulletRnder(enemybullet->GetPosition());
			//	SE���Đ�����
			AudioManager::GetInstance()->PlaySoundEffectSE(L"Hit_RF_Bullet_SE01");
		}
	}
}

/// <summary>
/// �g�p���Ă���v���C���[�̓����蔻����X�V
/// </summary>
void ColisionObjects::ColisionPlayer()
{
	//	�ʏ�G
	for (const auto& enemy : m_enemys)
	{
		//	�G�����G��Ԃ����S�A�j���[�V�������Ȃ珈�����s��Ȃ�
		if (enemy->IsInvincible() || enemy->IsDeadAnimation())	continue;

		//	�v���C���[�ƒʏ�̓G�Ƃ̓����蔻��
		if (Collision::CheckSphereAndSphere(m_player->GetSphere(), enemy->GetSphereCollision()))
		{
			//	�������Z�o
			DirectX::SimpleMath::Vector3 direction = Collision::HitDirectionSphereAndSphere(m_player->GetSphere(), enemy->GetSphereCollision());

			//	�ˌ��G && �G���ˌ����Ȃ�v���C���[�𐁂���΂�
			if (enemy->GetType() == Object::ObjectType::TackleEnemy && enemy->IsRedyAbility())
			{
				//	�v���C���[�Ƀ_���[�W��^����
				m_player->Damege(enemy->GetPower(), direction, PlayScene::TACLE_ENEMY_REACTION);
			}
			else
			{
				//	�v���C���[�Ƀ_���[�W��^����
				m_player->Damege(enemy->GetPower(), direction, PlayScene::OTHER_ENEMY_REACTION);
			}

			//	�G�ƃv���C���[�̋������𗣂�
			enemy->HitPlayer(direction, -1.0f);
			//	�G�t�F�N�g��\��
			m_playScene->HitRnder(m_player->GetPosition());
			//	SE���Đ�����
			AudioManager::GetInstance()->PlaySoundEffectSE(L"Hit_Player_SE01");
		}

		//	�v���C���[���U���� && �G�����G��ԂȂ珈�����s��
		if (Collision::CheckCapsuleAndSphere(m_player->GetSordCapuselColision(), enemy->GetSphereCollision()) && m_player->IsAttack())
		{
			//	�G�Ƀ_���[�W��^����
			enemy->Damege(m_player->GetPower());

			//	�ˌ���ԁ@&& �ˌ��G�Ȃ� �X�^����Ԃ�
			if (enemy->IsRedyAbility() && enemy->GetType() == Object::ObjectType::TackleEnemy)
			{
				//	�X�^����Ԃɂ���
				enemy->SwoonMode();
			}

			//	�G�t�F�N�g��`��
			m_playScene->HitRnder(enemy->GetPosition(), enemy.get());
			//	SE���Đ�����
			AudioManager::GetInstance()->PlaySoundEffectSE(L"Hit_Bullet_SE01");
		}
	}
}

/// <summary>
/// �G�����̓����蔻��
/// </summary>
void ColisionObjects::ColisionEnemies()
{
	//	�G
	for (auto it1 = m_enemys.begin(); it1 != m_enemys.end(); ++it1)
	{
		//	�G
		for (auto it2 = std::next(it1); it2 != m_enemys.end(); ++it2)
		{
			//	�G���m�̐ڐG����
			if (Collision::CheckSphereAndSphere((*it1)->GetSphereCollision(), (*it2)->GetSphereCollision()))
			{
				DirectX::SimpleMath::Vector3 direction = Collision::HitDirectionSphereAndSphere((*it1)->GetSphereCollision(), (*it2)->GetSphereCollision());
				//	�G�Ƌ����𗣂�
				(*it1)->HitEnemyMove(direction);
			}
		}
	}
}

/// <summary>
/// �G�����̍��G�͈�
/// </summary>
void ColisionObjects::InEnemiesSearch()
{
	//	�ʏ�G
	for (const auto& enemy : m_enemys)
	{
		//	�v���C���[�ƓG
		if (Collision::CheckSphereAndSphere(m_player->GetSphere(), enemy->GetSearchCollision())) { enemy->SetHateMode(); }
	}
}

/// <summary>
/// �G�����̓������
/// </summary>
void ColisionObjects::InEnemiesAbility()
{
	//	�ʏ�G
	for (const auto& enemy : m_enemys)
	{
		//	�G���ǔ���Ԃł͂Ȃ��Ȃ珈�����s��Ȃ�
		if (!enemy->IsHate())	continue;

		//	�v���C���[�ƓG
		if (Collision::CheckSphereAndSphere(m_player->GetSphere(), enemy->GetAbilityColision())) { enemy->SetInAbility(true); } else { enemy->SetInAbility(false); }
	}
}