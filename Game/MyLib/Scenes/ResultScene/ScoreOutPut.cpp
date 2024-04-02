

#include "pch.h"
#include "ScoreOutPut.h"

#include "Common/ReadData.h"

#include "Game/MyLib/GameDatas/Number.h"
#include "Game/MyLib/GameDatas/PlayInfo.h"

//	スコアの座標
const DirectX::SimpleMath::Vector2 ScoreOutPut::SCORE_POSITION		  = DirectX::SimpleMath::Vector2(670.0f, 320.0f);
//	スコアの真ん中の座標
const DirectX::SimpleMath::Vector2 ScoreOutPut::SCORE_ORIGIN_POSITION = DirectX::SimpleMath::Vector2(383.0f, 390.0f);

/// <summary>
/// コンストラクタ
/// </summary>
ScoreOutPut::ScoreOutPut()
{
}

/// <summary>
/// デストラクタ
/// </summary>
ScoreOutPut::~ScoreOutPut()
{
	AudioManager::GetInstance()->StopSoundEffect(L"Result_NumberChange");
}

/// <summary>
/// 初期化処理
/// </summary>
void ScoreOutPut::Initialize()
{
	//	番号画像
	//m_numTexture = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"number");

	//	スコア表示の作成
	m_pScore = std::make_unique<Number>
		(
			MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"number"),
			DirectX::SimpleMath::Vector2(740.0f, 275.0f)
		);

	////	通常敵
	//m_pNormalKnock = std::make_unique<Number>(DirectX::SimpleMath::Vector2(800.0f, 300.0f));
	////	突撃敵
	//m_pTackleKnock = std::make_unique<Number>(DirectX::SimpleMath::Vector2(800.0f, 350.0f));
	////	ボス敵
	//m_pBossKnock   = std::make_unique<Number>(DirectX::SimpleMath::Vector2(800.0f, 400.0f));
	
	//	プレイインフォ
	m_pPlayInfo = PlayInfo::GetInstance();

	//for (int i = 0; i < 3; i++)
	//{
	//	if(i / 3 ==0)
	//	m_pPlayInfo->KnockNormal();
	//	if(i / 2 == 0)
	//	m_pPlayInfo->KnockTackle();
	//	if(i / 5 == 0)
	//	m_pPlayInfo->KnockBoss();

	//	m_pPlayInfo->UpScore(3500);
	//}
}

/// <summary>
/// 更新処理
/// </summary>
bool ScoreOutPut::Update()
{
	m_pScore->Update(m_pPlayInfo->GetScore());
	//m_pNormalKnock->Update(m_pPlayInfo->GetNormalKnockNum());
	//m_pTackleKnock->Update(m_pPlayInfo->GetTackleKnockNum());
	//m_pBossKnock->Update(m_pPlayInfo->GetBossKnockNum());

	//	スコアが一緒なら描画を可能にする
	if (m_pScore->GetScore() == m_pPlayInfo->GetScore())
	{
		AudioManager::GetInstance()->StopSoundEffect(L"Result_NumberChange");
		return true;
	}

	//	SEを再生する
	AudioManager::GetInstance()->PlaySoundEffectRoopSE(L"Result_NumberChange");

	return false;
}

/// <summary>
/// 描画する
/// </summary>
void ScoreOutPut::Draw()
{
	//	案内キーの描画



	//	描画を行う
	m_pScore->DrawNumber(2.0f, 0.8f);

	//	描画を行う
	//m_pNormalKnock->DrawNumber();
	//m_pTackleKnock->DrawNumber();
	//m_pBossKnock->DrawNumber();

#pragma region DEBUG

	//std::wostringstream oss;
	//oss << "score:" << m_pPlayInfo->GetScore();
	//MyLib::ScreenResources::GetInstance()->RenderDebugFont(oss.str().c_str(), DirectX::SimpleMath::Vector2(500.0f, 220.0f));

	//std::wostringstream oss2;
	//oss2 << "normal:" << m_pPlayInfo->GetNormalKnockNum();
	//MyLib::ScreenResources::GetInstance()->RenderDebugFont(oss2.str().c_str(), DirectX::SimpleMath::Vector2(500.0f, 320.0f));
	//
	//std::wostringstream oss3;
	//oss3 << "tackle:" << m_pPlayInfo->GetTackleKnockNum();
	//MyLib::ScreenResources::GetInstance()->RenderDebugFont(oss3.str().c_str(), DirectX::SimpleMath::Vector2(500.0f, 350.0f));
	//
	//std::wostringstream oss4;
	//oss4 << "boss:" << m_pPlayInfo->GetBossKnockNum();
	//MyLib::ScreenResources::GetInstance()->RenderDebugFont(oss4.str().c_str(), DirectX::SimpleMath::Vector2(500.0f, 380.0f));
	//
	//std::wostringstream oss5;
	//oss5 << "time:" << m_pPlayInfo->GetElapseedTime();
	//MyLib::ScreenResources::GetInstance()->RenderDebugFont(oss5.str().c_str(), DirectX::SimpleMath::Vector2(500.0f, 400.0f));
#pragma endregion
}