#pragma once

class BossEnemy;
class NormalEnemy;
class TackleEnemy;

//	インターフェイスを宣言する	
__interface IEnemyFactory
{
	// 「通常敵」を生成する
	std::unique_ptr<NormalEnemy> CreateNormalEnemies(const DirectX::SimpleMath::Vector3& position, const int& health, const int& power, const int& level);
	// 「突撃敵」を生成する
	std::unique_ptr<TackleEnemy>  CreateTackleEnemies(const DirectX::SimpleMath::Vector3& position, const int& health, const int& power, const int& level);
	// 「ボス敵」を生成する
	std::unique_ptr<BossEnemy>  CreateBossEnemies(const DirectX::SimpleMath::Vector3& position, const int& health, const int& power, const int& level);
};