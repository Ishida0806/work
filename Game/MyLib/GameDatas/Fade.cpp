
#include "pch.h"
#include "Fade.h"

//	ラープタイム
const float Fade::LERP_TIME = 0.07f;
//	終わるタイム
const float Fade::FIN_TIME  = 0.03f;

/// <summary>
/// コンストラクタ
/// </summary>
Fade::Fade()
	:m_second(0.0f),
	//m_alfa(0.0f),
	m_startFlag(false),
	m_finFlag(false)
{
}

/// <summary>
/// デストラクタ
/// </summary>
Fade::~Fade()
{
}

/// <summary>
/// 初期化処理
/// </summary>
void Fade::Initialize()
{
	//	スクリーンリソースを取得する
	m_screen = MyLib::ScreenResources::GetInstance();
	//	リソーシーズデータを取得する
	m_resources = MyLib::ResourcesData::GetInstance();
	//	画像のテクスチャを取得する

	//	変数を初期化
	/*m_second	= 0.0f;
	m_alfa		= 0.0f;
	m_startFlag = false;
	m_finFlag	= false;*/
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="timer"></param>
void Fade::Update(const DX::StepTimer& timer)
{

}

/// <summary>
/// 描画処理
/// </summary>
void Fade::Render()
{

}

/// <summary>
/// 初期化処理
/// </summary>
void Fade::Finalize()
{
}

/// <summary>
/// フェイドインを行う
/// </summary>
void Fade::StartFade()
{
	m_startFlag = true;
}