//
//		File Name ： StartSignal.cpp
//		Production： 2023/10/17
//		Author　　： 石田 恭一	
// 
//		スタートの合図
//	
#include "pch.h"
#include "StartSignal.h"

//	GO画像の真ん中の座標
const DirectX::SimpleMath::Vector2 StartSignal::ORIGIN_GO_POSITION	  = DirectX::SimpleMath::Vector2(62.5f, 37.5f);
//	READY画像の真ん中の座標
const DirectX::SimpleMath::Vector2 StartSignal::ORIGIN_READY_POSITION = DirectX::SimpleMath::Vector2(137.5f, 46.0f);
//	画像のデフォルトの大きさ
const DirectX::SimpleMath::Vector2 StartSignal::BASE_SCALE			  = DirectX::SimpleMath::Vector2(2.0f, 2.0f);
//	GOが出たときに少し揺れる
const float						   StartSignal::SHAKE_GO_POSITION	  = 1.0f;

/// <summary>
/// コンストラクタ
/// </summary>
StartSignal::StartSignal()
	:m_readyUi(nullptr),
	m_goUi(nullptr),
	m_renderState(STATE::IDLE)
{
	
}

/// <summary>
/// デストラクタ
/// </summary>
StartSignal::~StartSignal()
{
}

/// <summary>
/// 初期化処理
/// </summary>
void StartSignal::Initialize()
{
	// デバイス依存のリソースの初期化
	CreateDeviceDependentResources();
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="timer">タイマー</param>
void StartSignal::Update(const DX::StepTimer& timer)
{
	timer;

	switch (m_renderState)
	{
	case StartSignal::STATE::IDLE:
	{
		if (m_maxFadeCount - 1.6f <= *m_pNextCount)
		{
			//	指定されたSEを流す
			AudioManager::GetInstance()->PlaySoundEffectSE(L"PlayStartSE01");
			m_renderState = STATE::READY;			
		}
		break;
	}
	case StartSignal::STATE::READY:
	{
		if (m_maxFadeCount - 0.4f <= *m_pNextCount)
		{
			//	指定されたSEを流す
			AudioManager::GetInstance()->PlaySoundEffectSE(L"PlayStartSE02");
			m_renderState = STATE::GO;
		}
		break;
	}
	case StartSignal::STATE::GO:
	{
		//m_goPosition.x += Utility::CreateRandom(-5.0f, 5.0f);
		//m_goPosition.y += Utility::CreateRandom(-SHAKE_GO_POSITION, SHAKE_GO_POSITION);

		if (m_maxFadeCount <= *m_pNextCount)
		{
			m_renderState = STATE::FINISH;
		}
		break;
	}
	case StartSignal::STATE::FINISH:	return;		break;
	
	default:	break;
	}
}

/// <summary>
/// 描画する
/// </summary>
void StartSignal::Draw()
{
	using namespace DirectX::SimpleMath;

	//	スプライトバッチを取得する
	DirectX::SpriteBatch* spriteBatch = MyLib::ScreenResources::GetInstance()->GetSpriteBatch();

	//	READYの時のみ描画する
	if (m_renderState == STATE::READY)
	{
		spriteBatch->Draw
		(
			m_readyUi,
			m_readyPosition,
			nullptr,
			DirectX::Colors::White,
			0.0f,
			ORIGIN_READY_POSITION,
			BASE_SCALE
		);
	}
	//	GOの時のみ描画する
	else if (m_renderState == STATE::GO)
	{
		spriteBatch->Draw
		(
			m_goUi,
			m_goPosition,
			nullptr,
			DirectX::Colors::White,
			0.0f,
			ORIGIN_GO_POSITION,
			BASE_SCALE
		);
	}
}

/// <summary>
/// デバイス依存のリソースの初期化
/// </summary>
void StartSignal::CreateDeviceDependentResources()
{
	using namespace DirectX::SimpleMath;

	//	ReadyのUI画像
	m_readyUi = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"Ready_UI");
	//	GOのUI画像
	m_goUi	  = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"Go_UI");
	//	READY座標
	m_readyPosition = Vector2(640.0f, 360.0f);
	m_goPosition	= Vector2(640.0f, 360.0f);
}

/// <summary>
/// フェードに必要な時間を設定する
/// </summary>
/// <param name="pFadeTimer">フェードタイムのポインター</param>
/// <param name="fadeMaxTime">マックス時間</param>
void StartSignal::SetFadeTime(float* pFadeTimer, float fadeMaxTime)
{
	m_pNextCount = pFadeTimer;
	m_maxFadeCount = fadeMaxTime;
}