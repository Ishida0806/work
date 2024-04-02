//
//		File Name ： StageBackGround.cpp
//		Production： 2023/11/01
//		Author　　： 石田 恭一	
// 
//		背景画像の更新描画を行う
// 
#include "pch.h"
#include "StageBackGround.h"

#include "Common/ReadData.h"
#include "StageSelectScene.h"

//	夜明け前の色
const DirectX::SimpleMath::Vector4 StageBackGround::DAWN_COLOR		= { -0.0f, -0.0f, -0.3f, -0.3f };
//	朝の色
const DirectX::SimpleMath::Vector4 StageBackGround::MORNING_COLOR	= { 0.50f, 0.50f, 0.50f,  0.50f };
//	昼ごろの色
const DirectX::SimpleMath::Vector4 StageBackGround::DAYTIME_COLOR	= { 0.8f,   0.0f,  0.05f,  1.0f };
//	夜の色
const DirectX::SimpleMath::Vector4 StageBackGround::NIGHT_COLOR		= { -1.0f, -1.0f, -0.25f, 1.0f };

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="backGroundTexture">画像</param>
StageBackGround::StageBackGround(ID3D11ShaderResourceView* backGroundTexture, const int& maxStage)
	:m_backGroundTexture(backGroundTexture),
	m_maxStageNum(maxStage),
	m_stageBackGroundConstBuffer{}
{
}

/// <summary>
/// デストラクタ
/// </summary>
StageBackGround::~StageBackGround()
{
}

/// <summary>
/// 初期化処理
/// </summary>
void StageBackGround::Initialize()
{
	//	コンテキスト
	auto context = MyLib::ScreenResources::GetInstance()->GetDevice();
	//	デバイス
	auto device = MyLib::ScreenResources::GetInstance()->GetDevice();
	// ピクセルシェーダーの作成
	std::vector<uint8_t> psData = DX::ReadData(L"Resources/CSO/StageBackGroundPS.cso");
	//	ピクセルシェーダを作成
	DX::ThrowIfFailed
	(
		//	
		context->CreatePixelShader
		(
			psData.data(),
			psData.size(),
			nullptr, 
			m_PS_Stage.ReleaseAndGetAddressOf()
		)
	);

	//	初期化する
	m_stageBackGroundConstBuffer.Diffuse = DirectX::SimpleMath::Vector4(0.0f,0.0f,0.0f,0.0f);
	//シェーダーにデータを渡すためのコンスタントバッファ生成
	D3D11_BUFFER_DESC bd;
	//	メモリのブロックをゼロで埋める
	ZeroMemory(&bd, sizeof(bd));
	//	バッファーの読み取りと書き込み方法を特定
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	device->CreateBuffer(&bd, nullptr, &m_cBuffer);
}

/// <summary>
/// 更新処理
/// </summary>
void StageBackGround::Update(const int& selectStage)
{	
	//	セレクトされた状態
	StageSelectScene::CHOOSE_STAGE  stageState = static_cast<StageSelectScene::CHOOSE_STAGE>(selectStage);

	//	ステージ状態によって色を変える
	switch (stageState)
	{
	case StageSelectScene::CHOOSE_STAGE::STAGE_1:	m_targetColor = DAWN_COLOR;		break;
	case StageSelectScene::CHOOSE_STAGE::STAGE_2:	m_targetColor = MORNING_COLOR;  break;
	case StageSelectScene::CHOOSE_STAGE::STAGE_3:	m_targetColor = DAYTIME_COLOR;	break;
	case StageSelectScene::CHOOSE_STAGE::STAGE_4:	m_targetColor = NIGHT_COLOR;	break;
	case StageSelectScene::CHOOSE_STAGE::OverID:									break;
	default:																		break;
	}

	//	ディフューズに色を反映させる
	m_stageBackGroundConstBuffer.Diffuse = 
		DirectX::SimpleMath::Vector4::Lerp
		(
			m_stageBackGroundConstBuffer.Diffuse, 
			m_targetColor, 
			0.05f
		);
}


/// <summary>
/// 描画する
/// </summary>
void StageBackGround::Draw()
{
	//	スプライトバッチ
	DirectX::SpriteBatch* spriteBatch = MyLib::ScreenResources::GetInstance()->GetSpriteBatch();
	//	コンテキスト
	auto context = MyLib::ScreenResources::GetInstance()->GetDeviceContext();
	//	開始する前にシェーダをセットする
	spriteBatch->Begin
	(
		DirectX::SpriteSortMode_Immediate,
		nullptr,
		nullptr,
		nullptr,
		nullptr,
		[&]()
		{
			//	コンストバッファを更新する
			context->UpdateSubresource(m_cBuffer.Get(), 0, NULL, &m_stageBackGroundConstBuffer, 0, 0);
			// ピクセルシェーダ使用する定数バッファを設定
			ID3D11Buffer* cbuf_ps[] = { m_cBuffer.Get() };
			// スロット0はDirectXTKが使用しているのでスロット１を使用する
			context->PSSetConstantBuffers(1, 1, cbuf_ps);	
			//	画像を設定する
			context->PSSetShaderResources(1, 1, &m_backGroundTexture);
			//	ピクセルシェーダを設定する
			context->PSSetShader(m_PS_Stage.Get(), nullptr, 0);
		}
	);

	//	描画を行う
	spriteBatch->Draw
	(
		m_backGroundTexture,
		DirectX::SimpleMath::Vector2::Zero
	);

	//	描画を終了する
	spriteBatch->End();
}

/// <summary>
/// 終了処理
/// </summary>
void StageBackGround::Finalize()
{
	
}
