//	
//		File Name ： ParamManager.cpp
//		Production： 2023/4/02
//		Author　　： 石田 恭一	
// 
//		パラメータマネージャー
//	
#include "pch.h"
#include "ParamManager.h"
#include "Common/json.hpp"
#include <fstream>

std::unique_ptr<MyLib::ParamManager> MyLib::ParamManager::m_paramManager = nullptr;

/// <summary>
/// ParamManagerの取得
/// </summary>
/// <returns>自身のポインター</returns>
MyLib::ParamManager* MyLib::ParamManager::GetInstane()
{
	//	ヌルポなら生成
	if (m_paramManager == nullptr)
	{
		//	スクリーンクラスのインスタンスを生成する
		m_paramManager.reset(new MyLib::ParamManager());
	}
	//	スクリーンリソースクラスのインスタンスを取得する
	return m_paramManager.get();
}

void MyLib::ParamManager::LoadData()
{
	m_playerData;

	//	ファイルを開く
	std::ifstream raceTrackFile(L"Resources/Data/PlayerParam.json");
	//	字列を JSON として解析
	nlohmann::json raceTrackData = nlohmann::json::parse(raceTrackFile);
	//	最大ウェーブ数
	m_playerData.playerHealth			= raceTrackData["HEALTH"];

	//	座標
	auto positionData = raceTrackData["POSITION"];
	DirectX::SimpleMath::Vector3 position(positionData[0], positionData[1], positionData[2]);
	m_playerData.position				= position;

	//	モデルの大きさ
	auto playerModel = raceTrackData["PLAYER MODEL SCALE"];
	DirectX::SimpleMath::Vector3 modelScale(playerModel[0], playerModel[1], playerModel[2]);
	m_playerData.modelScale				= modelScale;

	m_playerData.turnSpeed				= raceTrackData["TURN SPEED"];
	m_playerData.winAnimationTime		= raceTrackData["WIN ANIMATION TIME"];
	m_playerData.deathAnimationTime		= raceTrackData["DEATH ANIMATION TIME"];
	m_playerData.gravity				= raceTrackData["GRAVITY"];
}
