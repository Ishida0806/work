//
//		File Name �F EnemyFactory.h
//		Production�F 2023/11/12
//		Author�@�@�F �Γc ����	
//	
#pragma once
#include "BossEnemy.h"
#include "NormalEnemy.h"
#include "TackleEnemy.h"
#include "IEnemyFactory.h"

class EnemyFactory : public IEnemyFactory
{
public:
	// �u�ʏ�G�v�𐶐�����
	static std::unique_ptr<NormalEnemy>  CreateNormalEnemies(const DirectX::SimpleMath::Vector3& position, const int& health, const int& power, const int& level, Object::ObjectType objType);
	// �u�ˌ��G�v�𐶐�����
	static std::unique_ptr<TackleEnemy>  CreateTackleEnemies(const DirectX::SimpleMath::Vector3& position, const int& health, const int& power, const int& level, Object::ObjectType objType);
	// �u�{�X�G�v�𐶐�����
	static std::unique_ptr<BossEnemy>	 CreateBossEnemies(const DirectX::SimpleMath::Vector3& position, const int& health, const int& power, const int& level, Object::ObjectType objType);
};