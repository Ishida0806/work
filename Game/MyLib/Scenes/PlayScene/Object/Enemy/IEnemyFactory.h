#pragma once

class BossEnemy;
class NormalEnemy;
class TackleEnemy;

//	�C���^�[�t�F�C�X��錾����	
__interface IEnemyFactory
{
	// �u�ʏ�G�v�𐶐�����
	std::unique_ptr<NormalEnemy> CreateNormalEnemies(const DirectX::SimpleMath::Vector3& position, const int& health, const int& power, const int& level);
	// �u�ˌ��G�v�𐶐�����
	std::unique_ptr<TackleEnemy>  CreateTackleEnemies(const DirectX::SimpleMath::Vector3& position, const int& health, const int& power, const int& level);
	// �u�{�X�G�v�𐶐�����
	std::unique_ptr<BossEnemy>  CreateBossEnemies(const DirectX::SimpleMath::Vector3& position, const int& health, const int& power, const int& level);
};