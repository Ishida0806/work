//
//		File Name ： ScreenResources.cpp
//		Production： 2023/6/01
//		Author　　： 石田 恭一	
// 
//		DirectXTKでよく使うクラスまとめたクラス
//
#include "pch.h"
#include "ScreenResources.h"

std::unique_ptr<MyLib::ScreenResources> MyLib::ScreenResources::m_screenResources = nullptr;

/// <summary>
/// ScreenResourcesを取得する
/// </summary>
/// <returns></returns>
MyLib::ScreenResources* const MyLib::ScreenResources::GetInstance()
{
	//	ヌルポなら生成
	if (m_screenResources == nullptr)
	{
		//	スクリーンクラスのインスタンスを生成する
		m_screenResources.reset(new MyLib::ScreenResources());
	}
	//	スクリーンリソースクラスのインスタンスを取得する
	return m_screenResources.get();
}

/// <summary>
/// コンストラクタ
/// </summary>
MyLib::ScreenResources::ScreenResources()
	:
	m_effectFactory(nullptr),					// デバイスリソース
	m_screen_W(1280),								// スクリーン幅
	m_screen_H(720),								// スクリーン高
	m_view{},									// ビュー行列
	m_projection{},								// 射影行列
	m_device(nullptr),							// デバイス
	m_context(nullptr)							// デバイスコンテキスト
{
}

/// <summary>
/// 初期化処理
/// </summary>
void MyLib::ScreenResources::Initialize()
{
	// デバイスリソース
	DX::DeviceResources* DR = DX::DeviceResources::GetInstance();

	//　デバイスを取得する
	m_device = DR->GetD3DDevice();
	//　デバイスコンテキストを取得する
	m_context = DR->GetD3DDeviceContext();
	//　エフェクトリファクトの作成
	m_effectFactory = std::make_unique<DirectX::EffectFactory>(m_device);
	//　共通ステートオブジェクトの作成
	m_states = std::make_unique<DirectX::CommonStates>(m_device);
	//	スプライトバッチの作成
	m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(m_context);
	//	スプライトフォントの作成
	m_spriteFont = std::make_unique<DirectX::SpriteFont>(m_device, L"Resources/Font/SegoeUI_18.spritefont");

	//	バッチエフェクトの作成
	m_batchEffect = std::make_unique<DirectX::BasicEffect>(m_device);
	m_batchEffect->SetTextureEnabled(true);
	m_batchEffect->SetVertexColorEnabled(true);

	void const* shaderByteCode;
	size_t byteCodeLength;
	m_batchEffect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);

	// インプットレイアウトを作成
	m_device->CreateInputLayout(
		DirectX::VertexPositionColorTexture::InputElements,
			DirectX::VertexPositionColorTexture::InputElementCount,
			shaderByteCode,
			byteCodeLength,
			m_inputLayout.GetAddressOf()
	);
}

/// <summary>
/// デバックフォント
/// </summary>
void MyLib::ScreenResources::RenderDebugFont(const wchar_t* character, const DirectX::SimpleMath::Vector2 position)
{
	// スプライトバッチを開始
	m_spriteBatch->Begin();
	// デバッグテキストを描画
	m_spriteFont->DrawString(m_spriteBatch.get(), character, position, DirectX::Colors::White);
	// スプライトバッチを終了
	m_spriteBatch->End();
}

/// <summary>
/// スクリーンサイズを取得する
/// </summary>
/// <param name="width">画面の横</param>
/// <param name="height">画面の高さ</param>
void MyLib::ScreenResources::GetScreenSize(int& screenWeight, int& screenHeight)
{
	screenWeight = m_screen_W;
	screenHeight = m_screen_H;
}

/// <summary>
/// スクリーンサイズを設定する
/// </summary>
/// <param name="width">画面の横</param>
/// <param name="height">画面の高さ</param>
void MyLib::ScreenResources::SetScreenSize(const int& width, const int& height)
{
	m_screen_W = width;
	m_screen_H = height;
}

/// <summary>
/// ビューマトリックスを設定する
/// </summary>
/// <param name="view">ビューマトリックス</param>
void MyLib::ScreenResources::SetViewMatrix(const DirectX::SimpleMath::Matrix& view)
{
	m_view = view; 
}


/// <summary>
/// プロジェクションマトリックスを設定する
/// </summary>
/// <param name="projection">プロジェクション</param>
void MyLib::ScreenResources::SetProjectionMatrix(const DirectX::SimpleMath::Matrix& projection)
{
	m_projection = projection; 
}
