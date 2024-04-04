//
//		File Name ： EdditPlayData.h
//		Production： 2024/4/04
//		Author　　： 石田 恭一	
// 
//		PlayDataの編集
//	
#pragma once

#include <fstream>
#include "Common/json.hpp"

class EdditPlayData
{
	//	関数
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	EdditPlayData()
		:
		m_playData{}
	{

	}

	~EdditPlayData() = default;

	/// <summary>
	/// プレイデータを開く
	/// </summary>
	void OpenPlayData()
	{
		//	ファイルを開く
		std::wstring playDataFileName = L"Resources/Data/PlayData.json";
		//	ファイルを開く
		std::ifstream playDataFile(playDataFileName);
		//	字列を JSON として解析
		m_playData = nlohmann::json::parse(playDataFile);
	}


	//	ゲーム初回起動
	bool IsFirstOpen()	   { return m_playData["FIRST_OPEN"]; }
	//	ステージ1はクリアしたか？
	bool IsClearedStage1() { return	m_playData["STAGE_1_CLEARED"]; }
	//	ステージ2はクリアしたか？
	bool IsClearedStage2() { return m_playData["STAGE_2_CLEARED"]; }
	//	ステージ3はクリアしたか？
	bool IsClearedStage3() { return m_playData["STAGE_3_CLEARED"]; }
	//	チュートリアルをクリア
	void CleardTutorial()  
	{ 
		m_playData["FIRST_OPEN"] = false; 

		//	セーブ
		std::ofstream o("Resources/Data/PlayData.json");
		o << std::setw(4) << m_playData << std::endl;
	}

	//	変数
private:

	//	プレイデータ
	nlohmann::json m_playData;
};