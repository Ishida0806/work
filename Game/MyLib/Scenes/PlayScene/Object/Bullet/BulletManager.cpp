//
//		File Name ： BulletManager.cpp
//		Production： 2023/7/02
//		Author　　： 石田 恭一
// 
//		弾の発射・配列を管理する
//
#include "pch.h"
#include "BulletManager.h"

#include "Game/MyLib/Scenes/PlayScene/Object/Bullet/Bullet.h"
#include "Game/MyLib/Scenes/PlayScene/Object/Bullet/BulletFactroy.h"
#include "Game/MyLib/Scenes/PlayScene/Object/Enemy/Enemy.h"
#include "Game/MyLib/Scenes/PlayScene/PlayScene.h"

//	敵の弾の攻撃力
const int BulletManager::ENEMY_BULLET_POWER   = 3;
//	ボスの弾の攻撃力
const int BulletManager::BOSS_BULLET_POWER	  = 9;
//	ボス弾の大きさ
const float BulletManager::BOSS_BULLET_SCLAE  = 0.7f;
//	通常敵の弾の大きさ
const float BulletManager::ENEMY_BULLET_SCLAE = 0.6f;


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="enemy">敵たち</param>
BulletManager::BulletManager(std::vector<std::shared_ptr<Enemy>>& enemy)
	:m_enemys(enemy)
{
}

/// <summary>
/// デストラクタ
/// </summary>
BulletManager::~BulletManager()
{
}

/// <summary>
/// 初期化処理
/// </summary>
void BulletManager::Initialize()
{
	//	ボスの敵の弾を作成する
	for (int index = 0; index < BossEnemy::BOSS_BULLETS_NUM; ++index)
	{
		//	敵の弾を作成する
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
	//	通常敵の弾を作成する
	for (int index = 0; index < NormalEnemy::ENEMY_BULLETS_NUM; ++index)
	{
		//	敵の球を作成する
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
/// 更新処理
/// </summary>
/// <param name="timer">タイマー</param>
void BulletManager::Update(const DX::StepTimer& timer)
{
	// 通常の弾を発射する
	ShotBossBullets();
	// ボスの弾を発射する
	ShotEnemyBullets();
	// 通常の弾を更新する
	UpdateNormalBullet(timer);
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="view">ビュー</param>
/// <param name="proj">プロジェクション</param>
void BulletManager::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	//	敵の弾をを更新する
	for (const auto& enemybullet : m_bullets)
	{
		//	砲弾を使用中か
		if (!enemybullet->IsUsed()) continue;

		//	描画する
		enemybullet->Render(view, proj);
	}
}

/// <summary>
/// 通常の弾を更新更新する
/// </summary>
/// <param name="timer">タイマー</param>
void BulletManager::UpdateNormalBullet(const DX::StepTimer& timer)
{
	for (const auto& enemybullet : m_bullets)
	{
		if (!enemybullet->IsUsed()) continue;

		// 更新する
		enemybullet->Update(timer);
	}
}

/// <summary>
/// 敵の弾を発射する
/// </summary>
void BulletManager::ShotEnemyBullets()
{
	for (const auto& enemy : m_enemys)
	{
		//	通常の敵以外は帰れ
		if (enemy->GetType() != Object::ObjectType::NormalEnemy)	continue;
		//	発射可能か？
		if (!enemy->IsRedyAbility()) continue;

		for (const auto& bullet : m_bullets)
		{
			//	敵のオーナーを取得する
			BulletFactory::OwnerID Owner = static_cast<BulletFactory::OwnerID>(bullet->GetOwner());
			//	ボスの弾以外は帰れ
			if (Owner != BulletFactory::OwnerID::ENEMY) continue;
			// 砲弾が使用中かどうかを調べる
			if (bullet->IsUsed())	continue;
			//	砲弾を飛弾させる
			bullet->SetUsed(true);
			//	砲弾が発射される位置を計算する 
			DirectX::SimpleMath::Vector3 offsetPos = DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(0.0f, 0.0f, 1.f), enemy->GetRotate());
			//	発射位置を設定する
			bullet->SetPosition(enemy->GetPosition() - offsetPos);
			//	角度がずれてるため補正
			DirectX::SimpleMath::Quaternion rotate = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(180.0f)) * enemy->GetRotate();
			//  発射角を設定する
			bullet->SetRotate(rotate);
			//	撃ち終わったらフラグを切る
			enemy->SetAbility(false);
			//	SEを再生する
			AudioManager::GetInstance()->PlaySoundEffectSE(L"SHOT_BULLET_SE01");
			break;
		}
	}
}

/// <summary>
/// ボスの弾を発射する
/// </summary>
void BulletManager::ShotBossBullets()
{
	for (const auto& enemy : m_enemys)
	{
		//	ボス敵以外は帰れ
		if (enemy->GetType() != Object::ObjectType::BossEnemy)	continue;
		//	発射可能か？
		if (!enemy->IsRedyAbility()) continue;

		for (const auto& bullet : m_bullets)
		{
			//	敵のオーナーを取得する
			BulletFactory::OwnerID Owner = static_cast<BulletFactory::OwnerID>(bullet->GetOwner());
			//	ボスの弾以外は帰れ
			if (Owner == BulletFactory::OwnerID::ENEMY) continue;
			// 砲弾が使用中かどうかを調べる
			if (bullet->IsUsed())	continue;
			//	砲弾を飛弾させる
			bullet->SetUsed(true);
			//	角度がずれてるため補正
			DirectX::SimpleMath::Quaternion OffsetRotate = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(90.0f)) * enemy->GetRotate();
			//	砲弾が発射される位置を計算する 
			DirectX::SimpleMath::Vector3 offsetPos = DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(0.0f, 0.0f, 3.f), OffsetRotate);
			//	発射位置を設定する
			bullet->SetPosition(enemy->GetPosition() + offsetPos);
			//  発射角を設定する
			bullet->SetRotate(OffsetRotate);
			//	撃ち終わったらフラグを切る
			enemy->SetAbility(false);
			//	SEを再生する
			AudioManager::GetInstance()->PlaySoundEffectSE(L"SHOT_BULLET_SE02");

			break;
		}
	}
}
