//	
//		File Name ： ParamManager.h
//		Production： 2023/4/02
//		Author　　： 石田 恭一	
// 
//		パラメータマネージャー
//	
#pragma once

namespace MyLib
{
	class ParamManager
	{
	public:

		//	取得
		static ParamManager* GetInstane();

	private:

		//	自身のポインターの格納庫
		static std::unique_ptr<ParamManager> m_paramManager;
	};
}