//
//		File Name ： ResourcesData.cpp
//		Production： 2023/6/12
//		Author　　： 石田 恭一	
// 
//		リソースデータへのポインタを作成するクラス
//	
#include "pch.h"
#include "ResourcesData.h"

//	アドレス
std::unique_ptr<MyLib::ResourcesData> MyLib::ResourcesData::m_resources = nullptr;

/// <summary>
///  Resourcesクラスのインスタンスを取得する
/// </summary>
/// <returns>ポインター</returns>
MyLib::ResourcesData* const MyLib::ResourcesData::GetInstance()
{
	if (m_resources == nullptr)
	{
		// Resourcesクラスのインスタンスを生成する
		m_resources.reset(new ResourcesData());
	}
	// Resourcesクラスのインスタンスを返す
	return m_resources.get();
}

/// <summary>
/// コンストラクタ
/// </summary>
MyLib::ResourcesData::ResourcesData()
	:
	m_device(nullptr),
	m_screen(nullptr)
{
}

/// <summary>
/// 初期化処理
/// </summary>
void MyLib::ResourcesData::Initialize()
{
	//	デバイス
	m_device = m_screen->GetDeviceResources()->GetD3DDevice();
	//	スクリーンリソース
	m_screen = MyLib::ScreenResources::GetInstance();
	// リソースディレクトリを設定する
	m_screen->GetFX()->SetDirectory(L"Resources/CMO");
} 

/// <summary>
/// 画像を追加する
/// </summary>
/// <param name="path">画像の名前</param>
void MyLib::ResourcesData::AddShaderResourceView(std::wstring path)
{
	std::wstring fliepath = L"Resources/Textures/" + path + L".png";

	DirectX::CreateWICTextureFromFile
	(
		m_device,
		fliepath.c_str(),
		nullptr,
		m_texturesData[path].ReleaseAndGetAddressOf()
	);
}

/// <summary>
/// モデルを追加する
/// </summary>
/// <param name="path">モデルの名前</param>
void MyLib::ResourcesData::AddModel(std::wstring path)
{
	std::wstring fliepath = L"Resources/CMO/" + path + L".cmo";

	m_modelsData[path] = DirectX::Model::CreateFromCMO
	(
		m_device,
		fliepath.c_str(),
		*m_screen->GetFX()
	);
}
