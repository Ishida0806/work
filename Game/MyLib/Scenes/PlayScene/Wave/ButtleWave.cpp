//
//		File Name �F ButtleWave.cpp
//		Production�F 2024/1/23
//		Author�@�@�F �Γc ����	
// 
//		�G�̃E�F�[�u���Ǘ�����
//
#include "pch.h"
#include "ButtleWave.h"
#include <fstream>
#include "Common/json.hpp"
#include "../PlayScene.h"
#include "../../PlayScene/Object/Enemy/EnemyManager.h"
#include "../../StageSelect/StageSelectScene.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="playScene">�v���C�V�[��</param>
ButtleWave::ButtleWave(PlayScene* playScene)
	:m_playScene(playScene),
	m_maxWave(0)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ButtleWave::~ButtleWave()
{
}

/// <summary>
/// �X�e�[�W�����J��
/// </summary>
/// <returns>�G�̏��</returns>
std::vector<EnemyData> ButtleWave::OpenMap()
{
	StageSelectScene::CHOOSE_STAGE stage = static_cast<StageSelectScene::CHOOSE_STAGE>(m_playScene->GetWordLevel());

	//	�I�΂ꂽ�X�e�[�W���Ō�̃X�e�[�W�Ȃ�s��Ȃ�
	if (stage == StageSelectScene::CHOOSE_STAGE::STAGE_4)	return 	std::vector<EnemyData>();

	// JSON�f�[�^�̉��
	std::wstring jsonFileName = L"Resources/Data/StageWave-" + std::to_wstring(m_playScene->GetWordLevel()) + L".json";
	//	�t�@�C�����J��
	std::ifstream enemyDataFile(jsonFileName);
	//	����� JSON �Ƃ��ĉ��
	nlohmann::json enemyData = nlohmann::json::parse(enemyDataFile);
	//	�ő�E�F�[�u��
	m_maxWave = enemyData["MaxWave"];
	//	�G�̏o���f�[�^
	std::vector<EnemyData>	enemyDatas;
	//	���W���擾����
	for (const auto& data : enemyData["EnemyData"])
	{
		//	���W
		DirectX::SimpleMath::Vector3 position(data[0], data[1], data[2]);
		//	���
		int enemyType = data[3];
		//	�̗�
		int health = data[4];
		//	��
		int power = data[5];
		//	�X�|�[������E�F�[�u
		int spawnWave = data[6];
		//	���W�E�^�C�v�E�̗́E�́E�X�|�[������E�F�[�u
		EnemyData ed(position, enemyType, health, power, spawnWave);
		//	�f�[�^������
		enemyDatas.push_back(ed);
	}

	return enemyDatas;
}
