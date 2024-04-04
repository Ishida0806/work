//
//		File Name �F EnemyManager.cpp
//		Production�F 2023/11/12
//		Author�@�@�F �Γc ����	
// 
//		�G�̃}�l�[�W���[
//	
#include "pch.h"
#include "EnemyManager.h"

#include "Game/MyLib/Scenes/PlayScene/PlayScene.h"
#include "Game/MyLib/Scenes/StageSelect/StageSelectScene.h"
#include "Game/MyLib/Scenes/PlayScene/Object/Enemy/Enemy.h"

//	�{�X�̗̑�
const int EnemyManager::BOSS_ENEMY_HELATH		 = 100;
//	�ʏ�̓G�̗̑�
const int EnemyManager::NORMAL_ENEMY_HELATH		 = 12;
//	�ˌ��G�̗̑�
const int EnemyManager::TACLE_ENEMY_HELATH		 = 13;
//	�{�X�̐����̌��E��	
const int EnemyManager::BOSS_ENEMY_RESTRICTION	 = 1;	
//	���ʂ̓G�̐������E��
const int EnemyManager::NORMAL_ENEMY_RESTRICTION = 9;
//	�ˌ��̓G�̐������E��
const int EnemyManager::TACLE_ENEMY_RESTRICTION  = 8;	
//	�{�X�̔������x
const float	EnemyManager::BOSS_ENEMY_POP_SPEED	 = 50.0f;
//	�ʏ�̓G�̔������x
const float EnemyManager::NORMAL_ENEMY_POP_SPEED = 9.5f;
//	�ˌ��̓G�̔������x
const float EnemyManager::TACLE_ENEMY_POP_SPEED  = 18.5f;
//	�ǔ����[�h�̌��E��
const int EnemyManager::HATE_ENEMY_NUM			 = 5;
//	��Փx�ɂ���đ����鐔
const int EnemyManager::INCREASE_WORLD_LEVEL	 = 2;
//	�G�̗�
const int EnemyManager::ENEMY_POWER				 = 1;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="playScene">�v���C�V�[��</param>
/// <param name="player">�v���C���[</param>
/// <param name="playSceneWave">�v���C�V�[���̃E�F�[�u</param>
EnemyManager::EnemyManager(PlayScene* playScene, Player* player, PlaySceneWave* playSceneWave)
	:m_playScene(playScene),
	m_player(player),
	m_playSceneWave(playSceneWave),
	m_playInfo(nullptr),
	m_normalEnemyInformation{},
	m_tackleEnemyInformation{},
	m_bossEnemyInformation{},
	m_hateReaction(0),
	m_normalReaction(0),
	m_tackleReaction(0)
{

}

/// <summary>s
/// �f�X�g���N�^
/// </summary>
EnemyManager::~EnemyManager()
{
}

/// <summary>
/// ����������
/// </summary>
void EnemyManager::Initialize()
{
	//	�A�h���X���擾����
	m_playInfo = PlayInfo::GetInstance();
	//	�G�̒ǔ���Ԃ̑���
	m_hateReaction = HATE_ENEMY_NUM + INCREASE_WORLD_LEVEL * m_playScene->GetWordLevel();
	//	�ʏ�G�̌��E������
	m_normalReaction = NORMAL_ENEMY_RESTRICTION + INCREASE_WORLD_LEVEL * m_playScene->GetWordLevel();
	//	�ˌ��G�̌��E������
	m_tackleReaction = TACLE_ENEMY_RESTRICTION  + INCREASE_WORLD_LEVEL * m_playScene->GetWordLevel();
	//	�X�|�[������G��I��
	SelectSpawnEnemy();
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void EnemyManager::Update(const DX::StepTimer& timer)
{
	//	�ŏ��ɗ����烊�Z�b�g����
	m_normalEnemyInformation.ResetCount();
	m_tackleEnemyInformation.ResetCount();
	m_bossEnemyInformation.ResetCount();

	for (const auto& enemy : m_enemys)
	{
		//	�G�̎��
		Object::ObjectType type = enemy->GetType();

		if (type == Object::ObjectType::NormalEnemy)
		{
			//	���ݐ��𑝂₷
			m_normalEnemyInformation.IncrementSize();
		}
		if (type == Object::ObjectType::TackleEnemy)
		{
			//	���ݐ��𑝂₷
			m_tackleEnemyInformation.IncrementSize();
		}
		if (type == Object::ObjectType::BossEnemy)
		{
			//	���ݐ��𑝂₷
			m_bossEnemyInformation.IncrementSize();
		}

		enemy->SetTargetPosition(m_player->GetPosition());
		enemy->Update(timer);
	}

	StageSelectScene::CHOOSE_STAGE stage = static_cast<StageSelectScene::CHOOSE_STAGE>(m_playScene->GetWordLevel());

	//	�ŏI�X�e�[�W�Ȃ�G���N���o��
	if (stage == StageSelectScene::CHOOSE_STAGE::STAGE_4)
	{
		// �G�������X�V
		UpdateNormalEnemies(timer);
		// �G�������X�V
		UpdateTackleEnemies(timer);
		// �{�X�������X�V
		UpdateBosses(timer);
	}
	else
	{
		//	�G�̐����[���Ȃ玟�̃E�F�[�u��
		if (m_enemys.size() == 0)
		{
			//	���̃E�F�[�u�ɍs��
			m_playSceneWave->NextWave();
			//	�X�|�[������G��I��
			SelectSpawnEnemy();
		}
	}
	//	���S�I�u�W�F�g��T��
	DeadObject();
}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="view">�r���[</param>
/// <param name="proj">�v���W�F�N�V����</param>
void EnemyManager::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	//	�G�̕`��
	for (const auto& enemy : m_enemys)			enemy->Render(view, proj);
}

/// <summary>
/// �I������
/// </summary>
void EnemyManager::Finalize()
{
	//	�G�̏I������
	for (const auto& enemy : m_enemys)			enemy->Finalize();
}

/// <summary>
/// �{�X�������X�V
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void EnemyManager::UpdateBosses(const DX::StepTimer& timer)
{
	//	�������E���𒴂����珈�����s��Ȃ�
	if (m_bossEnemyInformation.size() >= BOSS_ENEMY_RESTRICTION)	return;

	m_bossEnemyInformation.popTime += static_cast<float>(timer.GetElapsedSeconds());

	if (m_bossEnemyInformation.popTime >= BOSS_ENEMY_POP_SPEED)
	{
		//	�G�̌Ăяo��
		m_enemys.push_back
		(
			EnemyFactory::CreateBossEnemies(DirectX::SimpleMath::Vector3
			(
				Utility::CreateRandom(-25.0f, 25.0f), 0.0f, Utility::CreateRandom(-25.0f, 25.0f)),
				BOSS_ENEMY_HELATH,
				ENEMY_POWER,
				m_playScene->GetWordLevel(),
				Object::ObjectType::BossEnemy
			)
		);

		//	�������Ԃ����Z�b�g����
		m_bossEnemyInformation.popTime = 0.0f;
	}
}

/// <summary>
/// �ʏ�G�������X�V
/// </summary>
/// <param name="timer">�^�C�}�[<</param>
void EnemyManager::UpdateNormalEnemies(const DX::StepTimer& timer)
{
	//	�������E���𒴂����珈�����s��Ȃ�
	if (m_normalEnemyInformation.size() >= m_normalReaction)	return;
	
	//	�o�ߎ��Ԃ𑫂�
	m_normalEnemyInformation.popTime += static_cast<float>(timer.GetElapsedSeconds());

	if (m_normalEnemyInformation.popTime > NORMAL_ENEMY_POP_SPEED)
	{
		//	�G�̌Ăяo��
		m_enemys.push_back
		(
			EnemyFactory::CreateNormalEnemies
			(
				DirectX::SimpleMath::Vector3(Utility::CreateRandom(-25.0f, 25.0f), 0.0f, Utility::CreateRandom(-25.0f, 25.0f)),
				NORMAL_ENEMY_HELATH,
				ENEMY_POWER,
				m_playScene->GetWordLevel(),
				Object::ObjectType::NormalEnemy
			)
		);
		//	�������Ԃ����Z�b�g����
		m_normalEnemyInformation.popTime = 0.0f;
	}	
}

/// <summary>
/// �ˌ��G�������X�V
/// </summary>
/// <param name="timer">�^�C�}�[<</param>
void EnemyManager::UpdateTackleEnemies(const DX::StepTimer& timer)
{
	//	�������E���𒴂����珈�����s��Ȃ�
	if (m_tackleEnemyInformation.size() >= m_tackleReaction)	return;
	
	//	�o�ߎ��Ԃ𑫂�
	m_tackleEnemyInformation.popTime += static_cast<float>(timer.GetElapsedSeconds());

	if (m_tackleEnemyInformation.popTime >= TACLE_ENEMY_POP_SPEED)
	{
		//	�G�̌Ăяo��
		m_enemys.push_back
		(
			EnemyFactory::CreateTackleEnemies
			(
				DirectX::SimpleMath::Vector3(Utility::CreateRandom(-25.0f, 25.0f), 0.0f, Utility::CreateRandom(-25.0f, 25.0f)),
				TACLE_ENEMY_HELATH,
				ENEMY_POWER,
				m_playScene->GetWordLevel(),
				Object::ObjectType::TackleEnemy
			)
		);
		//	�������Ԃ����Z�b�g����
		m_tackleEnemyInformation.popTime = 0.0f;
	}	
}

/// <summary>
/// �G�����񂾂�폜
/// </summary>
void EnemyManager::DeadObject()
{
	// �����𖞂����G�I�u�W�F�N�g���폜
	m_enemys.erase(
		std::remove_if(
			m_enemys.begin(), m_enemys.end(),
			[&](const std::shared_ptr<Enemy>& enemy)
			{
				//	����ł��邩�H
				if (enemy->IsDead())
				{
					Object::ObjectType type = enemy->GetType();

					//	�ʏ�G
					if (type == Object::ObjectType::NormalEnemy)
					{
						//	�X�R�A���グ�Č��j�����J�E���g
						m_playInfo->UpScore(MyLib::ParamManager::GetInstane()->GetEnemyScore().normalScore);
						//	�|���������L�^����
						m_playInfo->KnockNormal();
						//	�o���l���擾���ݒ肷��
						m_player->GetPlayerEXPoint()->SetExperiencePoint(enemy->GetEXP());
					}
					//	�ˌ��G
					if (type == Object::ObjectType::TackleEnemy)
					{
						//	�X�R�A���グ�Č��j�����J�E���g
						m_playInfo->UpScore(MyLib::ParamManager::GetInstane()->GetEnemyScore().tacleScore);
						//	�|���������L�^����
						m_playInfo->KnockTackle();
						//	�o���l���擾���ݒ肷��
						m_player->GetPlayerEXPoint()->SetExperiencePoint(enemy->GetEXP());
					}
					//	�{�X�G
					if (type == Object::ObjectType::BossEnemy)
					{
						//	�X�R�A���グ�Č��j�����J�E���g
						m_playInfo->UpScore(MyLib::ParamManager::GetInstane()->GetEnemyScore().bossScore);
						//	�|���������L�^����
						m_playInfo->KnockBoss();
						//	�o���l���擾���ݒ肷��
						m_player->GetPlayerEXPoint()->SetExperiencePoint(enemy->GetEXP());
					}					
					// �G���폜�Ώۂ�
					return true;
				}
				// �G���폜�ΏۂƂ��Ȃ�
				return false;
			}
		),
		m_enemys.end()
	);


#ifdef _DEBUG
	if (MyLib::InputSystem::GetInstance()->GetKeyTracer()->pressed.F2)
	{
		m_enemys.erase(
			std::remove_if(
				m_enemys.begin(), m_enemys.end(),
				[&](const std::shared_ptr<Enemy>& enemy)
				{
					return !enemy->IsDead();
				}
			),
			m_enemys.end()
		);
	}
#endif // _DEBUG
}

/// <summary>
/// �ǔ����[�h�̓G�̐���T��
/// </summary>
void EnemyManager::FindHateEnemy()
{
	//	
	std::vector<Enemy*>	hateEnemys;

	for (const auto& enemy : m_enemys)
	{
		if (enemy->IsHate())
		{
			hateEnemys.push_back(enemy.get());
		}
	}

	if (hateEnemys.size() > m_hateReaction)
	{
		//	���������ɕ��ׂ�
		std::sort
		(
			hateEnemys.begin(), hateEnemys.end(),
			[&](const Enemy* enemy, const Enemy* enemy2)
			{
				return abs(enemy->GetPosition().x + enemy->GetPosition().z) > abs(enemy2->GetPosition().x + enemy2->GetPosition().z);
			}
		);

		for (int index = 0; index < hateEnemys.size(); ++index)
		{
			if (index < m_hateReaction)	continue;

			hateEnemys[index]->SetHate(false);
		}
	}
}

/// <summary>
///	�X�|�[������G��I��
/// </summary>
void EnemyManager::SelectSpawnEnemy()
{
	for (const auto& enemyData : m_playSceneWave->GetEnemyData())
	{
		//	���݂̃E�F�[�u���ƈႤ�Ȃ�A��
		if (enemyData.spawnWave != m_playSceneWave->GetCurrentWave())	continue;

		EnemyType enemyType = static_cast<EnemyType>(enemyData.enemyType);

		//	�G�̃^�C�v��I��
		switch (enemyType)
		{
		case EnemyManager::EnemyType::NormalEnemy:

			//	�G�̌Ăяo��
			m_enemys.push_back
			(
				EnemyFactory::CreateNormalEnemies
				(
					enemyData.position,
					enemyData.health,
					enemyData.power,
					m_playScene->GetWordLevel(),
					Object::ObjectType::NormalEnemy
				)
			);

			break;
		case EnemyManager::EnemyType::TackleEnemy:

			//	�G�̌Ăяo��
			m_enemys.push_back
			(
				EnemyFactory::CreateTackleEnemies
				(
					enemyData.position,
					enemyData.health,
					enemyData.power, 
					m_playScene->GetWordLevel(),
					Object::ObjectType::TackleEnemy
				)
			);
			break;
		case EnemyManager::EnemyType::BossEnemy:

			//	�G�̌Ăяo��
			m_enemys.push_back
			(
				EnemyFactory::CreateBossEnemies
				(
					enemyData.position,
					enemyData.health,
					enemyData.power,
					m_playScene->GetWordLevel(),
					Object::ObjectType::BossEnemy
				)
			);

			break;
		case EnemyManager::EnemyType::OverID:				break;
		default:											break;
		}
	}

	//	�f�[�^�͂Ƃꂽ�̂ŏo���������f�[�^�͍폜
	m_playSceneWave->DeleteSpawnedEnemyData();
}


/// <summary>
/// �G���쐬����
/// </summary>
/// <param name="enemy">�G</param>
void EnemyManager::CreateEnemy(const Object::ObjectType& enemy)
{
	//	�ʏ�G
	if (enemy == Object::ObjectType::NormalEnemy)
	{
		m_enemys.push_back
		(
			EnemyFactory::CreateNormalEnemies
			(
				DirectX::SimpleMath::Vector3::Zero,
				NORMAL_ENEMY_HELATH,
				ENEMY_POWER,
				m_playScene->GetWordLevel(),
				Object::ObjectType::NormalEnemy
			)
		);
	}
	//	�ˌ��G
	else if (enemy == Object::ObjectType::TackleEnemy)
	{
		m_enemys.push_back
		(
			EnemyFactory::CreateTackleEnemies
			(
				DirectX::SimpleMath::Vector3::Zero,
				TACLE_ENEMY_HELATH,
				ENEMY_POWER,
				m_playScene->GetWordLevel(),
				Object::ObjectType::TackleEnemy
			)
		);
	}
	//	�{�X�G
	else if (enemy == Object::ObjectType::BossEnemy)
	{
		m_enemys.push_back
		(
			EnemyFactory::CreateTackleEnemies
			(
				DirectX::SimpleMath::Vector3::Zero,
				BOSS_ENEMY_HELATH,
				ENEMY_POWER,
				m_playScene->GetWordLevel(),
				Object::ObjectType::BossEnemy
			)
		);
	}
}