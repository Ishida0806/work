//
//		File Name ： ButtleWave.cpp
//		Production： 2024/1/23
//		Author　　： 石田 恭一	
// 
//		敵のウェーブを管理する
//
#include "pch.h"
#include "ButtleWave.h"
#include <fstream>
#include "Common/json.hpp"
#include "../PlayScene.h"
#include "../../PlayScene/Object/Enemy/EnemyManager.h"
#include "../../StageSelect/StageSelectScene.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="playScene">プレイシーン</param>
ButtleWave::ButtleWave(PlayScene* playScene)
	:m_playScene(playScene),
	m_maxWave(0)
{
}

/// <summary>
/// デストラクタ
/// </summary>
ButtleWave::~ButtleWave()
{
}

/// <summary>
/// ステージ情報を開く
/// </summary>
/// <returns>敵の情報</returns>
std::vector<EnemyData> ButtleWave::OpenMap()
{
	StageSelectScene::CHOOSE_STAGE stage = static_cast<StageSelectScene::CHOOSE_STAGE>(m_playScene->GetWordLevel());

	//	選ばれたステージが最後のステージなら行わない
	if (stage == StageSelectScene::CHOOSE_STAGE::STAGE_4)	return 	std::vector<EnemyData>();

	// JSONデータの解析
	std::wstring jsonFileName = L"Resources/Data/StageWave-" + std::to_wstring(m_playScene->GetWordLevel()) + L".json";
	//	ファイルを開く
	std::ifstream enemyDataFile(jsonFileName);
	//	字列を JSON として解析
	nlohmann::json enemyData = nlohmann::json::parse(enemyDataFile);
	//	最大ウェーブ数
	m_maxWave = enemyData["MaxWave"];
	//	敵の出現データ
	std::vector<EnemyData>	enemyDatas;
	//	座標を取得する
	for (const auto& data : enemyData["EnemyData"])
	{
		//	座標
		DirectX::SimpleMath::Vector3 position(data[0], data[1], data[2]);
		//	種類
		int enemyType = data[3];
		//	体力
		int health = data[4];
		//	力
		int power = data[5];
		//	スポーンするウェーブ
		int spawnWave = data[6];
		//	座標・タイプ・体力・力・スポーンするウェーブ
		EnemyData ed(position, enemyType, health, power, spawnWave);
		//	データを入れる
		enemyDatas.push_back(ed);
	}

	return enemyDatas;
}
