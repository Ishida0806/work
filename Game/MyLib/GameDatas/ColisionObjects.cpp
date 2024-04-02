
#include "pch.h"
#include "ColisionObjects.h"

#include "Game/MyLib/Scenes/PlayScene/PlayScene.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="playScene">プレイシーン</param>
/// <param name="player">プレイヤー<</param>
/// <param name="enemys">敵達</param>
/// <param name="bullets">弾</param>
/// <param name="walls">壁</param>
/// <param name="items">アイテム</param>
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
/// 特殊効果
/// </summary>
void ColisionObjects::UpdateAbility()
{
	//	プレイヤーが技能範囲内にいるか
	InEnemiesAbility();
}

/// <summary>
/// 当たり判定の更新
/// </summary>
void ColisionObjects::UpdateColision()
{
	//	アイテムの当たり判定
	UpdateItem();
	//	プレイヤーの当たり判定の更新
	ColisionPlayer();
	//	弾の当たり判定の更新
	ColisionBullets();
	//	敵同士の衝突判定
	ColisionEnemies();
	//	敵の索敵範囲に入ってないか？
	InEnemiesSearch();
}

/// <summary>
/// アイテムの当たり判定
/// </summary>
void ColisionObjects::UpdateItem()
{
	for (const auto& item : m_items)
	{
		//	取得アニメーション中なら帰れ
		if (item->IsTookAnimation())		continue;

		//	アイテムとプレイヤーの当たり判定
		if (Collision::CheckSphereAndSphere(item->GetSpere(), m_player->GetSphere()))
		{
			Item::ItemType itemType = item->GetItemType();

			//	パワーアップアイテム
			if (itemType == Item::ItemType::PowUp)
			{
				//	アイテムを取得状態に
				item->TookItem();
				//	パワーアップを取得する
				m_player->GetPowerUPItem();
				//	指定されたSEを流す
				AudioManager::GetInstance()->PlaySoundEffectSE(L"PowerUP");
			}
			//	回復アイテム
			else if (itemType == Item::ItemType::Recovery)
			{
				//	アイテムを取得状態に
				item->TookItem();
				//	回復を取得する
				m_player->GetRecoveryItem();
				//	指定されたSEを流す
				AudioManager::GetInstance()->PlaySoundEffectSE(L"RecoverSE01");
			}
			//	反射アイテム
			else if (itemType == Item::ItemType::Reflect)
			{
				//	アイテムを取得状態に
				item->TookItem();



				//	指定されたSEを流す
				AudioManager::GetInstance()->PlaySoundEffectSE(L"HaveWeapon");
			}
		}
	}
}

/// <summary>
/// 使用している弾の当たり判定を更新
/// </summary>
void ColisionObjects::ColisionBullets()
{
	//	敵の弾
	for (const auto& enemybullet : m_bullets)
	{
		//	プレイヤーの弾が未使用なら処理を行わない
		if (!enemybullet->IsUsed()) continue;

		//	弾が壁にあたったら未使用状態に
		for (const auto& wall : m_walls)
		{
			//	敵の弾が壁にあたったら未使用状態に
			if (Collision::CheckBoxAndSphereCollision(wall->GetWallBox(), enemybullet->GetSphere()))
			{
				//	壁に当たったら未使用状態に
				enemybullet->SetUsed(false);
			}
		}

		//	敵
		for (const auto& enemy : m_enemys)
		{
			//	敵が無敵状態か死亡アニメーション中なら処理を行わない
			if (enemy->IsInvincible() || enemy->IsDeadAnimation())	continue;

			//	プレイヤーが攻撃中なら処理を行う
			if (Collision::CheckCapsuleAndSphere(m_player->GetSordCapuselColision(), enemy->GetSphereCollision()) && m_player->IsAttack())
			{
				//	敵にダメージを与える
				enemy->Damege(m_player->GetPower());
				//	エフェクトを描画
				m_playScene->HitRnder(enemy->GetPosition(),enemy.get());
				//	SEを再生する
				AudioManager::GetInstance()->PlaySoundEffectSE(L"Hit_Bullet_SE01");
			}

			//	弾が反射中か？
			if (!enemybullet->IsReslect()) continue;

			//	敵と反射状態の敵の弾
			if (Collision::CheckSphereAndSphere(enemy->GetSphereCollision(), enemybullet->GetSphere()))
			{
				//	敵の弾を未使用状態に
				enemybullet->SetUsed(false);

				//	敵に当たれば反射する
				//enemybullet->Refrection(enemy->GetPosition());
				//	敵にダメージを与える
				enemy->Damege(m_player->GetPower() * 2);
				//	エフェクトを描画
				m_playScene->HitRnder(enemy->GetPosition(), enemy.get());
				//	SEを再生する
				AudioManager::GetInstance()->PlaySoundEffectSE(L"Hit_Bullet_SE01");
			}
		}

		//	プレイヤーと敵の弾 && 弾が反射状態じゃない && プレイヤーが無敵じゃないなら
		if (Collision::CheckSphereAndSphere(m_player->GetSphere(), enemybullet->GetSphere()) && !enemybullet->IsReslect() && !m_player->IsInvincible())
		{
			//	敵の弾を未使用状態に
			enemybullet->SetUsed(false);
			//	プレイヤーにダメージを与える
			m_player->Damege(enemybullet->GetPower(), Collision::HitDirectionSphereAndSphere(m_player->GetSphere(), enemybullet->GetSphere()));
			//	エフェクトを描画
			m_playScene->HitRnder(m_player->GetPosition());
			//	SEを再生する
			AudioManager::GetInstance()->PlaySoundEffectSE(L"Hit_Player_SE01");
		}

		// プレイヤーが攻撃中じゃないなら帰れ
		if (!m_player->IsAttack()) continue;

		// 剣のカプセルと敵の球の判定をとる && 敵の弾が反射状態じゃないなら
		if (Collision::CheckCapsuleAndSphere(m_player->GetSordCapuselColision(), enemybullet->GetSphere()))
		{		
			//	反射処理
			enemybullet->Refrection(m_player->GetPosition());
			//	無敵にしてあげる
			m_player->SetInvincible(true);
			//	ヒットエフェクト描画
			m_playScene->HitBulletRnder(enemybullet->GetPosition());
			//	SEを再生する
			AudioManager::GetInstance()->PlaySoundEffectSE(L"Hit_RF_Bullet_SE01");
		}
	}
}

/// <summary>
/// 使用しているプレイヤーの当たり判定を更新
/// </summary>
void ColisionObjects::ColisionPlayer()
{
	//	通常敵
	for (const auto& enemy : m_enemys)
	{
		//	敵が無敵状態か死亡アニメーション中なら処理を行わない
		if (enemy->IsInvincible() || enemy->IsDeadAnimation())	continue;

		//	プレイヤーと通常の敵との当たり判定
		if (Collision::CheckSphereAndSphere(m_player->GetSphere(), enemy->GetSphereCollision()))
		{
			//	向きを算出
			DirectX::SimpleMath::Vector3 direction = Collision::HitDirectionSphereAndSphere(m_player->GetSphere(), enemy->GetSphereCollision());

			//	突撃敵 && 敵が突撃中ならプレイヤーを吹っ飛ばす
			if (enemy->GetType() == Object::ObjectType::TackleEnemy && enemy->IsRedyAbility())
			{
				//	プレイヤーにダメージを与える
				m_player->Damege(enemy->GetPower(), direction, PlayScene::TACLE_ENEMY_REACTION);
			}
			else
			{
				//	プレイヤーにダメージを与える
				m_player->Damege(enemy->GetPower(), direction, PlayScene::OTHER_ENEMY_REACTION);
			}

			//	敵とプレイヤーの距離をを離す
			enemy->HitPlayer(direction, -1.0f);
			//	エフェクトを表示
			m_playScene->HitRnder(m_player->GetPosition());
			//	SEを再生する
			AudioManager::GetInstance()->PlaySoundEffectSE(L"Hit_Player_SE01");
		}

		//	プレイヤーが攻撃中 && 敵が無敵状態なら処理を行う
		if (Collision::CheckCapsuleAndSphere(m_player->GetSordCapuselColision(), enemy->GetSphereCollision()) && m_player->IsAttack())
		{
			//	敵にダメージを与える
			enemy->Damege(m_player->GetPower());

			//	突撃状態　&& 突撃敵なら スタン状態に
			if (enemy->IsRedyAbility() && enemy->GetType() == Object::ObjectType::TackleEnemy)
			{
				//	スタン状態にする
				enemy->SwoonMode();
			}

			//	エフェクトを描画
			m_playScene->HitRnder(enemy->GetPosition(), enemy.get());
			//	SEを再生する
			AudioManager::GetInstance()->PlaySoundEffectSE(L"Hit_Bullet_SE01");
		}
	}
}

/// <summary>
/// 敵たちの当たり判定
/// </summary>
void ColisionObjects::ColisionEnemies()
{
	//	敵
	for (auto it1 = m_enemys.begin(); it1 != m_enemys.end(); ++it1)
	{
		//	敵
		for (auto it2 = std::next(it1); it2 != m_enemys.end(); ++it2)
		{
			//	敵同士の接触判定
			if (Collision::CheckSphereAndSphere((*it1)->GetSphereCollision(), (*it2)->GetSphereCollision()))
			{
				DirectX::SimpleMath::Vector3 direction = Collision::HitDirectionSphereAndSphere((*it1)->GetSphereCollision(), (*it2)->GetSphereCollision());
				//	敵と距離を離す
				(*it1)->HitEnemyMove(direction);
			}
		}
	}
}

/// <summary>
/// 敵たちの索敵範囲
/// </summary>
void ColisionObjects::InEnemiesSearch()
{
	//	通常敵
	for (const auto& enemy : m_enemys)
	{
		//	プレイヤーと敵
		if (Collision::CheckSphereAndSphere(m_player->GetSphere(), enemy->GetSearchCollision())) { enemy->SetHateMode(); }
	}
}

/// <summary>
/// 敵たちの特殊効果
/// </summary>
void ColisionObjects::InEnemiesAbility()
{
	//	通常敵
	for (const auto& enemy : m_enemys)
	{
		//	敵が追尾状態ではないなら処理を行わない
		if (!enemy->IsHate())	continue;

		//	プレイヤーと敵
		if (Collision::CheckSphereAndSphere(m_player->GetSphere(), enemy->GetAbilityColision())) { enemy->SetInAbility(true); } else { enemy->SetInAbility(false); }
	}
}