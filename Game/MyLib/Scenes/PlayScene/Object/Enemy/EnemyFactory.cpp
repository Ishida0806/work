//
//		File Name �F EnemyFactory.cpp
//		Production�F 2023/11/12
//		Author�@�@�F �Γc ����	
// 
//		�G�̍H��
//	
#pragma once
#include "pch.h"
#include "EnemyFactory.h"

/// <summary>
/// �ʏ�G���쐬
/// </summary>
/// <param name="position">���W/param>
/// <param name="health">�̗�</param>
/// <param name="power">��</param>
/// <param name="level">���x��</param>
/// <returns>���L��</returns>
std::unique_ptr<NormalEnemy> EnemyFactory::CreateNormalEnemies(const DirectX::SimpleMath::Vector3& position, const int& health, const int& power, const int& level, Object::ObjectType objType)
{
	std::unique_ptr<NormalEnemy> enemy;

	enemy.reset(new NormalEnemy(position, health, power, level, objType));
	enemy->Initialize();

	return std::move(enemy);
}

/// <summary>
///	�ˌ��G���쐬
/// </summary>
/// <param name="position">���W</param>
/// <param name="health">�̗�</param>
/// <param name="power">��</param>
/// <param name="level">���x��</param>
/// <returns>���L��</returns>
std::unique_ptr<TackleEnemy> EnemyFactory::CreateTackleEnemies(const DirectX::SimpleMath::Vector3& position, const int& health, const int& power, const int& level, Object::ObjectType objType)
{
	std::unique_ptr<TackleEnemy> enemy;

	enemy.reset(new TackleEnemy(position, health, power, level, objType));
	enemy->Initialize();

	return std::move(enemy);
}

/// <summary>
///	�{�X�G���쐬
/// </summary>
/// <param name="position">���W</param>
/// <param name="health">�̗�</param>
/// <param name="power">��</param>
/// <param name="level">���x��</param>
/// <returns>���L��</returns>
std::unique_ptr<BossEnemy> EnemyFactory::CreateBossEnemies(const DirectX::SimpleMath::Vector3& position, const int& health, const int& power, const int& level, Object::ObjectType objType)
{
	std::unique_ptr<BossEnemy> boss;

	boss.reset(new BossEnemy(position, health, power, level, objType));
	boss->Initialize();

	return std::move(boss);
}
