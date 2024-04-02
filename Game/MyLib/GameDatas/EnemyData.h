//
//		File Name �F EnemyData.h
//		Production�F 2024/1/23
//		Author�@�@�F �Γc ����	
// 
//		JSON�t�@�C����ǂݍ��ލۂ̏���w�b�_�[
//
#pragma once

struct EnemyData
{
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="position">���W</param>
	/// <param name="enemyType">���ʎq</param>
	/// <param name="power">��</param>
	/// <param name="health">�̗�</param>
	/// <param name="spawnWave">�X�|�[������E�F�[�u��</param>
	EnemyData(const DirectX::SimpleMath::Vector3& position, const int& enemyType, const int& health, const int& power, const int& spawnWave)
		:
		position(position),
		enemyType(enemyType),
		health(health),
		power(power),
		spawnWave(spawnWave)
	{

	}

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~EnemyData() = default;

	//	�ϐ�
public:

	//	�G�̃^�C�v
	int							 enemyType;
	//	�X�|�[���E�F�[�u
	int							 spawnWave;
	//	�̗�
	int							 health;
	//	��
	int							 power;
	//	���W
	DirectX::SimpleMath::Vector3 position;
};