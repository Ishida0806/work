//
//		File Name �F EdditPlayData.h
//		Production�F 2024/4/04
//		Author�@�@�F �Γc ����	
// 
//		PlayData�̕ҏW
//	
#pragma once

#include <fstream>
#include "Common/json.hpp"

class EdditPlayData
{
	//	�֐�
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	EdditPlayData()
		:
		m_playData{}
	{

	}

	~EdditPlayData() = default;

	/// <summary>
	/// �v���C�f�[�^���J��
	/// </summary>
	void OpenPlayData()
	{
		//	�t�@�C�����J��
		std::wstring playDataFileName = L"Resources/Data/PlayData.json";
		//	�t�@�C�����J��
		std::ifstream playDataFile(playDataFileName);
		//	����� JSON �Ƃ��ĉ��
		m_playData = nlohmann::json::parse(playDataFile);
	}


	//	�Q�[������N��
	bool IsFirstOpen()	   { return m_playData["FIRST_OPEN"]; }
	//	�X�e�[�W1�̓N���A�������H
	bool IsClearedStage1() { return	m_playData["STAGE_1_CLEARED"]; }
	//	�X�e�[�W2�̓N���A�������H
	bool IsClearedStage2() { return m_playData["STAGE_2_CLEARED"]; }
	//	�X�e�[�W3�̓N���A�������H
	bool IsClearedStage3() { return m_playData["STAGE_3_CLEARED"]; }
	//	�`���[�g���A�����N���A
	void CleardTutorial()  
	{ 
		m_playData["FIRST_OPEN"] = false; 

		//	�Z�[�u
		std::ofstream o("Resources/Data/PlayData.json");
		o << std::setw(4) << m_playData << std::endl;
	}

	//	�ϐ�
private:

	//	�v���C�f�[�^
	nlohmann::json m_playData;
};