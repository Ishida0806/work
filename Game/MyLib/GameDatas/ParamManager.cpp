//	
//		File Name �F ParamManager.cpp
//		Production�F 2023/4/02
//		Author�@�@�F �Γc ����	
// 
//		�p�����[�^�}�l�[�W���[
//	
#include "pch.h"
#include "ParamManager.h"
#include "Common/json.hpp"
#include <fstream>

std::unique_ptr<MyLib::ParamManager> MyLib::ParamManager::m_paramManager = nullptr;

/// <summary>
/// ParamManager�̎擾
/// </summary>
/// <returns>���g�̃|�C���^�[</returns>
MyLib::ParamManager* const MyLib::ParamManager::GetInstane()
{
	//	�k���Ȃ琶��
	if (m_paramManager == nullptr)
	{
		//	�X�N���[���N���X�̃C���X�^���X�𐶐�����
		m_paramManager.reset(new MyLib::ParamManager());
	}
	//	�X�N���[�����\�[�X�N���X�̃C���X�^���X���擾����
	return m_paramManager.get();
}

/// <summary>
/// �R���X�g���N�^
/// </summary>
MyLib::ParamManager::ParamManager()
	:
	m_playerData{},
	m_enemyScore{}
{

}

/// <summary>
/// ���[�h�f�[�^
/// </summary>
void MyLib::ParamManager::LoadData()
{
	// �v���C���[�̃p�����[�^�̃��[�h
	LoadPlayerData();
	// �G�̃X�R�A�̃��[�h
	LoadEnemyScore();
}


/// <summary>
/// �v���C���[�̃p�����[�^�̃��[�h
/// </summary>
void MyLib::ParamManager::LoadPlayerData()
{
	std::wstring jsonFileName = L"Resources/Data/PlayerParam.json";
	//	�t�@�C�����J��
	std::ifstream raceTrackFile(jsonFileName);
	//	����� JSON �Ƃ��ĉ��
	nlohmann::json playerParamkData = nlohmann::json::parse(raceTrackFile);
	//	�ő�E�F�[�u��
	m_playerData.playerHealth = playerParamkData["HEALTH"];
	//	���W���擾����
	const auto& positionData = playerParamkData["POSITION"];
	//	���W
	DirectX::SimpleMath::Vector3		  position(positionData[0], positionData[1], positionData[2]);
	m_playerData.position = position;
	//	���f���̑傫��
	const auto& playerScaleData = playerParamkData["PLAYER_MODEL_SCALE"];
	//	���f���̑傫��
	DirectX::SimpleMath::Vector3		modelScale(playerScaleData[0], playerScaleData[1], playerScaleData[2]);
	m_playerData.modelScale = modelScale;
	//	�U��������x
	m_playerData.turnSpeed = playerParamkData["TURN_SPEED"];
	//	�������̃A�j���[�V����
	m_playerData.winAnimationTime = playerParamkData["WIN_ANIMATION_TIME"];
	//	���S���̃A�j���[�V����
	m_playerData.deathAnimationTime = playerParamkData["DEATH_ANIMATION_TIME"];
	//	�d��
	m_playerData.gravity = playerParamkData["GRAVITY"];
}

/// <summary>
/// �G�̃X�R�A�̃��[�h
/// </summary>
void MyLib::ParamManager::LoadEnemyScore()
{
	std::wstring enemyScoreFileName = L"Resources/Data/EnemyScore.json";
	//	�t�@�C�����J��
	std::ifstream enemyScoreFile(enemyScoreFileName);
	//	����� JSON �Ƃ��ĉ��
	nlohmann::json enemyData = nlohmann::json::parse(enemyScoreFile);
	//	�G�̒ʏ�X�R�A
	m_enemyScore.normalScore = enemyData["NORMAL_ENEMY_SCORE"];
	//	�ˌ��̒ʏ�X�R�A
	m_enemyScore.tacleScore = enemyData["TACLE_ENEMY_SCORE"];
	//	�{�X�̒ʏ�X�R�A
	m_enemyScore.bossScore = enemyData["BOSS_ENEMY_SCORE"];
}

