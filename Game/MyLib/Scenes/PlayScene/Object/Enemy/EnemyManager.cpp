//
//		File Name ： EnemyManager.cpp
//		Production： 2023/11/12
//		Author　　： 石田 恭一	
// 
//		敵のマネージャー
//	
#include "pch.h"
#include "EnemyManager.h"

#include "Game/MyLib/Scenes/PlayScene/PlayScene.h"
#include "Game/MyLib/Scenes/StageSelect/StageSelectScene.h"
#include "Game/MyLib/Scenes/PlayScene/Object/Enemy/Enemy.h"

//	ボスの体力
const int EnemyManager::BOSS_ENEMY_HELATH		 = 100;
//	通常の敵の体力
const int EnemyManager::NORMAL_ENEMY_HELATH		 = 12;
//	突撃敵の体力
const int EnemyManager::TACLE_ENEMY_HELATH		 = 13;
//	ボスの生成の限界数	
const int EnemyManager::BOSS_ENEMY_RESTRICTION	 = 1;	
//	普通の敵の生成限界数
const int EnemyManager::NORMAL_ENEMY_RESTRICTION = 9;
//	突撃の敵の生成限界数
const int EnemyManager::TACLE_ENEMY_RESTRICTION  = 8;	
//	ボスの発生速度
const float	EnemyManager::BOSS_ENEMY_POP_SPEED	 = 50.0f;
//	通常の敵の発生速度
const float EnemyManager::NORMAL_ENEMY_POP_SPEED = 9.5f;
//	突撃の敵の発生速度
const float EnemyManager::TACLE_ENEMY_POP_SPEED  = 18.5f;
//	追尾モードの限界数
const int EnemyManager::HATE_ENEMY_NUM			 = 5;
//	難易度によって増える数
const int EnemyManager::INCREASE_WORLD_LEVEL	 = 2;
//	敵の力
const int EnemyManager::ENEMY_POWER				 = 1;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="playScene">プレイシーン</param>
/// <param name="player">プレイヤー</param>
/// <param name="playSceneWave">プレイシーンのウェーブ</param>
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
/// デストラクタ
/// </summary>
EnemyManager::~EnemyManager()
{
}

/// <summary>
/// 初期化処理
/// </summary>
void EnemyManager::Initialize()
{
	//	アドレスを取得する
	m_playInfo = PlayInfo::GetInstance();
	//	敵の追尾状態の総数
	m_hateReaction = HATE_ENEMY_NUM + INCREASE_WORLD_LEVEL * m_playScene->GetWordLevel();
	//	通常敵の限界生成数
	m_normalReaction = NORMAL_ENEMY_RESTRICTION + INCREASE_WORLD_LEVEL * m_playScene->GetWordLevel();
	//	突撃敵の限界生成数
	m_tackleReaction = TACLE_ENEMY_RESTRICTION  + INCREASE_WORLD_LEVEL * m_playScene->GetWordLevel();
	//	スポーンする敵を選ぶ
	SelectSpawnEnemy();
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="timer">タイマー</param>
void EnemyManager::Update(const DX::StepTimer& timer)
{
	//	最初に来たらリセットする
	m_normalEnemyInformation.ResetCount();
	m_tackleEnemyInformation.ResetCount();
	m_bossEnemyInformation.ResetCount();

	for (const auto& enemy : m_enemys)
	{
		//	敵の種類
		Object::ObjectType type = enemy->GetType();

		if (type == Object::ObjectType::NormalEnemy)
		{
			//	存在数を増やす
			m_normalEnemyInformation.IncrementSize();
		}
		if (type == Object::ObjectType::TackleEnemy)
		{
			//	存在数を増やす
			m_tackleEnemyInformation.IncrementSize();
		}
		if (type == Object::ObjectType::BossEnemy)
		{
			//	存在数を増やす
			m_bossEnemyInformation.IncrementSize();
		}

		enemy->SetTargetPosition(m_player->GetPosition());
		enemy->Update(timer);
	}

	StageSelectScene::CHOOSE_STAGE stage = static_cast<StageSelectScene::CHOOSE_STAGE>(m_playScene->GetWordLevel());

	//	最終ステージなら敵が湧き出す
	if (stage == StageSelectScene::CHOOSE_STAGE::STAGE_4)
	{
		// 敵たちを更新
		UpdateNormalEnemies(timer);
		// 敵たちを更新
		UpdateTackleEnemies(timer);
		// ボスたちを更新
		UpdateBosses(timer);
	}
	else
	{
		//	敵の数がゼロなら次のウェーブで
		if (m_enemys.size() == 0)
		{
			//	次のウェーブに行く
			m_playSceneWave->NextWave();
			//	スポーンする敵を選ぶ
			SelectSpawnEnemy();
		}
	}
	//	死亡オブジェトを探す
	DeadObject();
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="view">ビュー</param>
/// <param name="proj">プロジェクション</param>
void EnemyManager::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	//	敵の描画
	for (const auto& enemy : m_enemys)			enemy->Render(view, proj);
}

/// <summary>
/// 終了処理
/// </summary>
void EnemyManager::Finalize()
{
	//	敵の終了処理
	for (const auto& enemy : m_enemys)			enemy->Finalize();
}

/// <summary>
/// ボスたちを更新
/// </summary>
/// <param name="timer">タイマー</param>
void EnemyManager::UpdateBosses(const DX::StepTimer& timer)
{
	//	生成限界数を超えたら処理を行わない
	if (m_bossEnemyInformation.size() >= BOSS_ENEMY_RESTRICTION)	return;

	m_bossEnemyInformation.popTime += static_cast<float>(timer.GetElapsedSeconds());

	if (m_bossEnemyInformation.popTime >= BOSS_ENEMY_POP_SPEED)
	{
		//	敵の呼び出し
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

		//	生成時間をリセットする
		m_bossEnemyInformation.popTime = 0.0f;
	}
}

/// <summary>
/// 通常敵たちを更新
/// </summary>
/// <param name="timer">タイマー<</param>
void EnemyManager::UpdateNormalEnemies(const DX::StepTimer& timer)
{
	//	生成限界数を超えたら処理を行わない
	if (m_normalEnemyInformation.size() >= m_normalReaction)	return;
	
	//	経過時間を足す
	m_normalEnemyInformation.popTime += static_cast<float>(timer.GetElapsedSeconds());

	if (m_normalEnemyInformation.popTime > NORMAL_ENEMY_POP_SPEED)
	{
		//	敵の呼び出し
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
		//	生成時間をリセットする
		m_normalEnemyInformation.popTime = 0.0f;
	}	
}

/// <summary>
/// 突撃敵たちを更新
/// </summary>
/// <param name="timer">タイマー<</param>
void EnemyManager::UpdateTackleEnemies(const DX::StepTimer& timer)
{
	//	生成限界数を超えたら処理を行わない
	if (m_tackleEnemyInformation.size() >= m_tackleReaction)	return;
	
	//	経過時間を足す
	m_tackleEnemyInformation.popTime += static_cast<float>(timer.GetElapsedSeconds());

	if (m_tackleEnemyInformation.popTime >= TACLE_ENEMY_POP_SPEED)
	{
		//	敵の呼び出し
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
		//	生成時間をリセットする
		m_tackleEnemyInformation.popTime = 0.0f;
	}	
}

/// <summary>
/// 敵が死んだら削除
/// </summary>
void EnemyManager::DeadObject()
{
	// 条件を満たす敵オブジェクトを削除
	m_enemys.erase(
		std::remove_if(
			m_enemys.begin(), m_enemys.end(),
			[&](const std::shared_ptr<Enemy>& enemy)
			{
				//	死んでいるか？
				if (enemy->IsDead())
				{
					Object::ObjectType type = enemy->GetType();

					//	通常敵
					if (type == Object::ObjectType::NormalEnemy)
					{
						//	スコアを上げて撃破数をカウント
						m_playInfo->UpScore(MyLib::ParamManager::GetInstane()->GetEnemyScore().normalScore);
						//	倒した数を記録する
						m_playInfo->KnockNormal();
						//	経験値を取得し設定する
						m_player->GetPlayerEXPoint()->SetExperiencePoint(enemy->GetEXP());
					}
					//	突撃敵
					if (type == Object::ObjectType::TackleEnemy)
					{
						//	スコアを上げて撃破数をカウント
						m_playInfo->UpScore(MyLib::ParamManager::GetInstane()->GetEnemyScore().tacleScore);
						//	倒した数を記録する
						m_playInfo->KnockTackle();
						//	経験値を取得し設定する
						m_player->GetPlayerEXPoint()->SetExperiencePoint(enemy->GetEXP());
					}
					//	ボス敵
					if (type == Object::ObjectType::BossEnemy)
					{
						//	スコアを上げて撃破数をカウント
						m_playInfo->UpScore(MyLib::ParamManager::GetInstane()->GetEnemyScore().bossScore);
						//	倒した数を記録する
						m_playInfo->KnockBoss();
						//	経験値を取得し設定する
						m_player->GetPlayerEXPoint()->SetExperiencePoint(enemy->GetEXP());
					}					
					// 敵を削除対象と
					return true;
				}
				// 敵を削除対象としない
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
/// 追尾モードの敵の数を探す
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
		//	小さい順に並べる
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
///	スポーンする敵を選ぶ
/// </summary>
void EnemyManager::SelectSpawnEnemy()
{
	for (const auto& enemyData : m_playSceneWave->GetEnemyData())
	{
		//	現在のウェーブ数と違うなら帰れ
		if (enemyData.spawnWave != m_playSceneWave->GetCurrentWave())	continue;

		EnemyType enemyType = static_cast<EnemyType>(enemyData.enemyType);

		//	敵のタイプを選ぶ
		switch (enemyType)
		{
		case EnemyManager::EnemyType::NormalEnemy:

			//	敵の呼び出し
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

			//	敵の呼び出し
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

			//	敵の呼び出し
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

	//	データはとれたので出現させたデータは削除
	m_playSceneWave->DeleteSpawnedEnemyData();
}


/// <summary>
/// 敵を作成する
/// </summary>
/// <param name="enemy">敵</param>
void EnemyManager::CreateEnemy(const Object::ObjectType& enemy)
{
	//	通常敵
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
	//	突撃敵
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
	//	ボス敵
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