#include "pch.h"
#include "ParamManager.h"

std::unique_ptr<MyLib::ParamManager> MyLib::ParamManager::m_paramManager = nullptr;

/// <summary>
/// ParamManagerの取得
/// </summary>
/// <returns>自身のポインター</returns>
ParamManager* ParamManager::GetInstane()
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
