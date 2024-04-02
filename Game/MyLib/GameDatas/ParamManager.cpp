//	
//		File Name ： ParamManager.cpp
//		Production： 2023/4/02
//		Author　　： 石田 恭一	
// 
//		パラメータマネージャー
//	
#include "pch.h"
#include "ParamManager.h"

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
		m_paramManager.reset(new ParamManager());
	}
	//	スクリーンリソースクラスのインスタンスを取得する
	return m_paramManager.get();
}
