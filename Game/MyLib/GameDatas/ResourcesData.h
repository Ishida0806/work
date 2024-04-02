//
//		File Name ： ResourcesData.h
//		Production： 2023/6/12（改訂日：10/25）
//		Author　　： 石田 恭一	
//	
#pragma once
#include <unordered_map>

// Resourcesクラスを定義する
namespace MyLib
{
	class ResourcesData
	{
		//	アクセサ
	public:

		/// <summary>
		/// 画像を取得する
		/// </summary>
		/// <param name="path">パス</param>
		/// <returns>ID3D11ShaderResourceView</returns>
		inline ID3D11ShaderResourceView* GatShaderResourceView(const std::wstring& path) const { return m_texturesData.at(path).Get(); }

		/// <summary>
		/// モデルを取得する
		/// </summary>
		/// <param name="path">パス</param>
		/// <returns>Model</returns>
		inline DirectX::Model* GatModel(const std::wstring& path)						 const { return m_modelsData.at(path).get(); }
			
		/// <summary>
		/// 画像の要素を追加する
		/// </summary>
		/// <param name="path">パス</param>
		void AddShaderResourceView(std::wstring path);

		/// <summary>
		/// モデルを追加する
		/// </summary>
		/// <param name="path">パス</param>
		void AddModel(std::wstring path);


	public:
		// Resoucesクラスのインスタンスを取得する
		static ResourcesData* const GetInstance();
		//	初期化する
		void Initialize();

	private:
		// コンストラクタ
		ResourcesData();
		// 代入は許容しない
		void operator=(const ResourcesData& object) = delete;
		// コピーコンストラクタは許容しない
		ResourcesData(const ResourcesData& object) = delete;

	private:
		// Resourcesクラスのインスタンスへのポインタ
		static std::unique_ptr<ResourcesData> m_resources;
		// グラフィックス
		MyLib::ScreenResources*															   m_screen;
		// デバイス
		//Microsoft::WRL::ComPtr<ID3D11Device>											   m_device;
		ID3D11Device* m_device;
		//	画像のデータ
		std::unordered_map<std::wstring, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_texturesData;
		//	モデルのデータ
		std::unordered_map<std::wstring, std::unique_ptr<DirectX::Model>>				   m_modelsData;
	};
}