//
//		File Name ： EnemyFactory.h
//		Production： 2023/11/12
//		Author　　： 石田 恭一	
//	
#pragma once
#include "BossEnemy.h"
#include "NormalEnemy.h"
#include "TackleEnemy.h"
#include "IEnemyFactory.h"

class EnemyFactory : public IEnemyFactory
{
public:
	// 「通常敵」を生成する
	static std::unique_ptr<NormalEnemy>  CreateNormalEnemies(const DirectX::SimpleMath::Vector3& position, const int& health, const int& power, const int& level, Object::ObjectType objType);
	// 「突撃敵」を生成する
	static std::unique_ptr<TackleEnemy>  CreateTackleEnemies(const DirectX::SimpleMath::Vector3& position, const int& health, const int& power, const int& level, Object::ObjectType objType);
	// 「ボス敵」を生成する
	static std::unique_ptr<BossEnemy>	 CreateBossEnemies(const DirectX::SimpleMath::Vector3& position, const int& health, const int& power, const int& level, Object::ObjectType objType);
};