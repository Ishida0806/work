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
		//	�t�@�C��path
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


	// �`���[�g���A�����N���A
	void CleardTutorial()
	{
		m_playData["FIRST_OPEN"] = false;

		// �t�@�C����ǂݎ�菑�����݃��[�h�ŊJ��
		std::fstream file("Resources/Data/PlayData.json", std::ios::in | std::ios::out | std::ios::binary);

		if (file.is_open()) 
		{
			// JSON �f�[�^��ǂݍ���
			nlohmann::json jsonData;
			file >> jsonData;

			// "FIRST_OPEN" �̒l���X�V
			jsonData["FIRST_OPEN"] = false;

			// �t�@�C�������
			file.close();

			// �t�@�C�����������݃��[�h�ōēx�J���i���e����ɂ���j
			file.open("Resources/Data/PlayData.json", std::ios::out | std::ios::trunc);

			// �X�V���ꂽ JSON ���t�@�C���ɏ�������
			file << std::setw(4) << jsonData << std::endl;

			// �t�@�C�������
			file.close();
		}
	}



	//	�ϐ�
private:

	//	�v���C�f�[�^
	nlohmann::json m_playData;
};