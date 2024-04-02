//	
//		File Name �F ParamManager.h
//		Production�F 2023/4/02
//		Author�@�@�F �Γc ����	
// 
//		�p�����[�^�}�l�[�W���[
//	
#pragma once
#include "PlayerData.h"

namespace MyLib
{
	class ParamManager
	{
	public:



		//	�擾
		static ParamManager* GetInstane();

		//	�v���C���[�̃f�[�^���擾����
		PlayerData GetPlayerData()	const { return m_playerData; }

		void LoadData();

	private:


		// �R���X�g���N�^
		ParamManager();
		// ����͋��e���Ȃ�
		void operator=(const ParamManager& object) = delete;
		// �R�s�[�R���X�g���N�^�͋��e���Ȃ�
		ParamManager(const ParamManager& object) = delete;

	private:

		//	���g�̃|�C���^�[�̊i�[��
		static std::unique_ptr<ParamManager> m_paramManager;

		PlayerData							 m_playerData;
	};
}