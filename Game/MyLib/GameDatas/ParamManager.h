//	
//		File Name ： ParamManager.h
//		Production： 2023/4/02
//		Author　　： 石田 恭一	
// 
//		パラメータマネージャー
//	
#pragma once
#include "PlayerData.h"

namespace MyLib
{
	class ParamManager
	{
	public:



		//	取得
		static ParamManager* GetInstane();

		//	プレイヤーのデータを取得する
		PlayerData GetPlayerData()	const { return m_playerData; }

		void LoadData();

	private:


		// コンストラクタ
		ParamManager();
		// 代入は許容しない
		void operator=(const ParamManager& object) = delete;
		// コピーコンストラクタは許容しない
		ParamManager(const ParamManager& object) = delete;

	private:

		//	自身のポインターの格納庫
		static std::unique_ptr<ParamManager> m_paramManager;

		PlayerData							 m_playerData;
	};
}