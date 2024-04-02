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
MyLib::ParamManager* const MyLib::ParamManager::GetInstane()
{
	//	ヌルなら生成
	if (m_paramManager == nullptr)
	{
		//	スクリーンクラスのインスタンスを生成する
		m_paramManager.reset(new MyLib::ParamManager());
	}
	//	スクリーンリソースクラスのインスタンスを取得する
	return m_paramManager.get();
}

/// <summary>
/// コンストラクタ
/// </summary>
MyLib::ParamManager::ParamManager()
	:
	m_playerData{}
{

}

/// <summary>
/// ロードデータ
/// </summary>
void MyLib::ParamManager::LoadData()
{
	std::wstring jsonFileName = L"Resources/Data/PlayerParam.json";
	//	ファイルを開く
	std::ifstream raceTrackFile(jsonFileName);
	//	字列を JSON として解析
	nlohmann::json playerParamkData		= nlohmann::json::parse(raceTrackFile);
	//	最大ウェーブ数
	m_playerData.playerHealth			= playerParamkData["HEALTH"];
	//	座標を取得する
	const auto& positionData			= playerParamkData["POSITION"];
	//	座標
	DirectX::SimpleMath::Vector3		  position(positionData[0], positionData[1], positionData[2]);
	m_playerData.position				= position;
	//	モデルの大きさ
	const auto& playerScaleData			= playerParamkData["PLAYER_MODEL_SCALE"];
	//	モデルの大きさ
	DirectX::SimpleMath::Vector3		modelScale(playerScaleData[0], playerScaleData[1], playerScaleData[2]);
	m_playerData.modelScale				= modelScale;
	//	振り向く速度
	m_playerData.turnSpeed				= playerParamkData["TURN_SPEED"];
	//	勝利時のアニメーション
	m_playerData.winAnimationTime		= playerParamkData["WIN_ANIMATION_TIME"];
	//	死亡時のアニメーション
	m_playerData.deathAnimationTime		= playerParamkData["DEATH_ANIMATION_TIME"];
	//	重力
	m_playerData.gravity				= playerParamkData["GRAVITY"];
}
