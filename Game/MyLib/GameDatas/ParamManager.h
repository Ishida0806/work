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
		//	変数
	public:


		//	取得
		static ParamManager* const GetInstane();
		//	プレイヤーのデータを取得する
		PlayerData& GetPlayerData() { return m_playerData; }

		//	データのロード
		void LoadData();

	private:

		// コンストラクタ
		ParamManager();
		// 代入は許容しない
		void operator=(const ParamManager& object) = delete;
		// コピーコンストラクタは許容しない
		ParamManager(const ParamManager& object) = delete;

		//	変数
	private:
		//	自身のポインターの格納庫
		static std::unique_ptr<ParamManager> m_paramManager;
		//	プレイヤーのデータ
		PlayerData							 m_playerData;
	};
}