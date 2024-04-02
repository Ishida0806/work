//
//		File Name ： EnemyFactory.cpp
//		Production： 2023/11/12
//		Author　　： 石田 恭一	
// 
//		敵の工場
//	
#pragma once
#include "pch.h"
#include "EnemyFactory.h"

/// <summary>
/// 通常敵を作成
/// </summary>
/// <param name="position">座標/param>
/// <param name="health">体力</param>
/// <param name="power">力</param>
/// <param name="level">レベル</param>
/// <returns>所有権</returns>
std::unique_ptr<NormalEnemy> EnemyFactory::CreateNormalEnemies(const DirectX::SimpleMath::Vector3& position, const int& health, const int& power, const int& level, Object::ObjectType objType)
{
	std::unique_ptr<NormalEnemy> enemy;

	enemy.reset(new NormalEnemy(position, health, power, level, objType));
	enemy->Initialize();

	return std::move(enemy);
}

/// <summary>
///	突撃敵を作成
/// </summary>
/// <param name="position">座標</param>
/// <param name="health">体力</param>
/// <param name="power">力</param>
/// <param name="level">レベル</param>
/// <returns>所有権</returns>
std::unique_ptr<TackleEnemy> EnemyFactory::CreateTackleEnemies(const DirectX::SimpleMath::Vector3& position, const int& health, const int& power, const int& level, Object::ObjectType objType)
{
	std::unique_ptr<TackleEnemy> enemy;

	enemy.reset(new TackleEnemy(position, health, power, level, objType));
	enemy->Initialize();

	return std::move(enemy);
}

/// <summary>
///	ボス敵を作成
/// </summary>
/// <param name="position">座標</param>
/// <param name="health">体力</param>
/// <param name="power">力</param>
/// <param name="level">レベル</param>
/// <returns>所有権</returns>
std::unique_ptr<BossEnemy> EnemyFactory::CreateBossEnemies(const DirectX::SimpleMath::Vector3& position, const int& health, const int& power, const int& level, Object::ObjectType objType)
{
	std::unique_ptr<BossEnemy> boss;

	boss.reset(new BossEnemy(position, health, power, level, objType));
	boss->Initialize();

	return std::move(boss);
}
