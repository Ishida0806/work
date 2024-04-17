
#include"pch.h"
#include"BatMeter.h"

//	バットメーターの真ん中
const DirectX::SimpleMath::Vector2 BatMeter::ORIGIN_BAT_METER		 = DirectX::SimpleMath::Vector2(50.5f, 75.1f);
//	バットメーターの側の真ん中
const DirectX::SimpleMath::Vector2 BatMeter::ORIGIN_BAT_SIDE_METER   = DirectX::SimpleMath::Vector2(69.0f, 104.0f);
//	バットメーターの真ん中座標
const DirectX::SimpleMath::Vector2 BatMeter::BAT_METER_POSITION		 = DirectX::SimpleMath::Vector2(1186.0f, 575.0f);
//	バットメーターの側の真ん中座標
const DirectX::SimpleMath::Vector2 BatMeter::BAT_SIDE_METER_POSITION = DirectX::SimpleMath::Vector2(1200.0f, 600.0f);

/// <summary>
/// コンストラクタ
/// </summary>
BatMeter::BatMeter()
{
}

BatMeter::~BatMeter()
{
}

/// <summary>
/// 初期化処理
/// </summary>
void BatMeter::Initialize()
{
	//	リソースデータ
	m_resources			= MyLib::ResourcesData::GetInstance();
	//	スクリーンリソース
	m_screen			= MyLib::ScreenResources::GetInstance();
	//	バットメーター
	m_batMeter		    = m_resources->GatShaderResourceView(L"BatMeter");
	//	バットの側メーター
	m_batSideMeter	    = m_resources->GatShaderResourceView(L"BatSide");
	//	バットメーターの真ん中座標
	m_batMeterPosition  = BAT_METER_POSITION;
	//	バットメーターの側の真ん中座標
	m_batMeterSidePosition  = BAT_SIDE_METER_POSITION;
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="timer">タイマー</param>
void BatMeter::Update(const DX::StepTimer& timer)
{

}

void BatMeter::Draw()
{
	//	バットメーターの描画
	m_screen->GetSpriteBatch()->Draw
	(
		m_batSideMeter,
		m_batMeterSidePosition,
		nullptr,
		DirectX::Colors::White,
		0.0f,
		ORIGIN_BAT_SIDE_METER
	);

	// バットメーターの側の描画
	m_screen->GetSpriteBatch()->Draw
	(
		m_batMeter,
		m_batMeterPosition,
		nullptr,
		DirectX::Colors::White,
		0.0f,
		ORIGIN_BAT_METER
	);
}

/// <summary>
/// デバイス依存のリソースの初期化
/// </summary>
void BatMeter::CreateDeviceDependentResources()
{
}

/// <summary>
/// ソードの設定
/// </summary>
/// <param name="sord">ソード</param>
void BatMeter::SetSord(Sord* sord)
{
	m_sord = sord;
}