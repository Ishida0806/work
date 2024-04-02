//
//		File Name ： ScreenResources.h
//		Production： 2023/6/01
//		Author　　： 石田 恭一	
//
#pragma once

#include "Common/DeviceResources.h"

namespace MyLib
{
	class ScreenResources final
	{
	private:
		// スクリーンリソーシーズクラスのインスタンスへのポインタ
		static std::unique_ptr<ScreenResources>		 m_screenResources;
		// エフェクトファクトリー					  
		std::unique_ptr<DirectX::EffectFactory>		 m_effectFactory;
		//	スプライトエフェクト					   
		std::unique_ptr<DirectX::BasicEffect>		 m_batchEffect;
		//	スプライトバッチ						 
		std::unique_ptr<DirectX::SpriteBatch>		 m_spriteBatch;
		//	スプライトフォント					    
		std::unique_ptr<DirectX::SpriteFont>		 m_spriteFont;
		// 共通ステートオブジェクトへのポインタ	   
		std::unique_ptr<DirectX::CommonStates>		 m_states;
		//	インプットレイアウトを作成
		Microsoft::WRL::ComPtr<ID3D11InputLayout>	 m_inputLayout;

		//スクリーンサイズ(横幅、縦幅)
		int m_screen_W;
		int m_screen_H;

		// ビュー行列
		DirectX::SimpleMath::Matrix m_view;
		// 射影行列
		DirectX::SimpleMath::Matrix m_projection;

		// デバイス
		ID3D11Device* m_device;
		// デバイスコンテキスト
		ID3D11DeviceContext* m_context;

		//	アクセサ
	public:
		//	スクリーンのインスタンスを取得する
		static ScreenResources*											const GetInstance();
		//	デバイスリソースを取得する
		inline DX::DeviceResources* GetDeviceResources()				const { return DX::DeviceResources::GetInstance(); }
		//	コモンステートを取得する
		inline DirectX::CommonStates* GetCommonState()					const { return m_states.get(); }
		//	エフェクトリファクトリクラスのインスタンスを取得する
		inline DirectX::EffectFactory* GetFX()							const { return m_effectFactory.get(); }
		//	ベーシックエフェクトを取得する
		inline DirectX::BasicEffect* GetBasicEffect()					const { return m_batchEffect.get(); }
		//	スプライトバッチを取得する
		inline DirectX::SpriteBatch* GetSpriteBatch()					const { return m_spriteBatch.get(); }
		//	インプットレイアウトの作成
		inline ID3D11InputLayout* GetInputLayout()						const { return m_inputLayout.Get(); }
		// ビュー行列を取得する
		inline const DirectX::SimpleMath::Matrix& GetViewMatrix()		const { return m_view; };
		// 射影行列を取得する
		inline const DirectX::SimpleMath::Matrix& GetProjectionMatrix()	const { return m_projection; }
		//	コンテキストを取得する
		inline ID3D11DeviceContext* GetDeviceContext()					const { return m_context; }
		// デバイスを取得する
		inline ID3D11Device* GetDevice()								const { return m_device; }
		//	スクリーンサイズを取得する
		void GetScreenSize(int& screenWeight, int& screenHeight);
		//	スクリーンサイズを設定する
		void SetScreenSize(const int& width, const int& height);
		// ビュー行列を設定する
		void SetViewMatrix(const DirectX::SimpleMath::Matrix& view);
		// 射影行列を設定する
		void SetProjectionMatrix(const DirectX::SimpleMath::Matrix& projection);

	private:

		//	コンストラクタ
		ScreenResources();

	public:

		void Initialize();
		void RenderDebugFont(const wchar_t* character , const DirectX::SimpleMath::Vector2 position );
	};
}
