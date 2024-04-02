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
MyLib::ParamManager* MyLib::ParamManager::GetInstane()
{
	//	�k���|�Ȃ琶��
	if (m_paramManager == nullptr)
	{
		//	�X�N���[���N���X�̃C���X�^���X�𐶐�����
		m_paramManager.reset(new MyLib::ParamManager());
	}
	//	�X�N���[�����\�[�X�N���X�̃C���X�^���X���擾����
	return m_paramManager.get();
}

void MyLib::ParamManager::LoadData()
{
	m_playerData;

	//	�t�@�C�����J��
	std::ifstream raceTrackFile(L"Resources/Data/PlayerParam.json");
	//	����� JSON �Ƃ��ĉ��
	nlohmann::json raceTrackData = nlohmann::json::parse(raceTrackFile);
	//	�ő�E�F�[�u��
	m_playerData.playerHealth			= raceTrackData["HEALTH"];

	//	���W
	auto positionData = raceTrackData["POSITION"];
	DirectX::SimpleMath::Vector3 position(positionData[0], positionData[1], positionData[2]);
	m_playerData.position				= position;

	//	���f���̑傫��
	auto playerModel = raceTrackData["PLAYER MODEL SCALE"];
	DirectX::SimpleMath::Vector3 modelScale(playerModel[0], playerModel[1], playerModel[2]);
	m_playerData.modelScale				= modelScale;

	m_playerData.turnSpeed				= raceTrackData["TURN SPEED"];
	m_playerData.winAnimationTime		= raceTrackData["WIN ANIMATION TIME"];
	m_playerData.deathAnimationTime		= raceTrackData["DEATH ANIMATION TIME"];
	m_playerData.gravity				= raceTrackData["GRAVITY"];
}
