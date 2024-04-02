//	
//		File Name �F ParamManager.h
//		Production�F 2023/4/02
//		Author�@�@�F �Γc ����	
// 
//		�p�����[�^�}�l�[�W���[
//	
#pragma once
#include "PlayerData.h"
#include "EnemyScore.h"

namespace MyLib
{
	class ParamManager
	{
		//	�ϐ�
	public:

		//	�擾
		static ParamManager* const GetInstane();
		//	�v���C���[�̃f�[�^���擾����
		PlayerData& GetPlayerData() { return m_playerData; }
		//	�G�l�~�[�̃f�[�^���擾����
		EnemyScore& GetEnemyScore()  { return m_enemyScore; }

		//	�f�[�^�̃��[�h
		void LoadData();

	private:

		// �R���X�g���N�^
		ParamManager();
		// ����͋��e���Ȃ�
		void operator=(const ParamManager& object) = delete;
		// �R�s�[�R���X�g���N�^�͋��e���Ȃ�
		ParamManager(const ParamManager& object) = delete;

		//	�ϐ�
	private:
		//	���g�̃|�C���^�[�̊i�[��
		static std::unique_ptr<ParamManager> m_paramManager;
		//	�v���C���[�̃f�[�^
		PlayerData							 m_playerData;
		//	�G�̃X�R�A�̃f�[�^
		EnemyScore							 m_enemyScore;

		//	���ߍ��݊֐�
	private:

		//	�v���C���[�̃p�����[�^�̃��[�h
		void LoadPlayerData();
		//	�G�̃X�R�A�̃��[�h
		void LoadEnemyScore();
	};
}