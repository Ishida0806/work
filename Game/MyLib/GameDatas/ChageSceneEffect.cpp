//
//		File Name ： ChageSceneEffect.cpp
//		Production： 2023/1/17
//		Author　　： 石田 恭一	
// 
//		シーン遷移の際のエフェクトの更新・描画
//
#include "pch.h"
#include "ChageSceneEffect.h"
#include "Game/Game.h"

#include "ChangeEffectPlay.h"
#include "ChangeEffectTitle.h"
#include "ChangeEffectResult.h"
#include "ChangeEffectStageSelect.h"

/// <summary>
/// 初期化処理
/// </summary>
/// <param name="game">ゲーム</param>
ChageSceneEffect::ChageSceneEffect(Game* game)
	:m_game(game)
{
}

/// <summary>
/// デストラクタ
/// </summary>
ChageSceneEffect::~ChageSceneEffect()
{
}

/// <summary>
/// 初期化処理
/// </summary>
void ChageSceneEffect::Initialize()
{
	//	
	m_fadeEffects.push_back(std::make_unique<ChangeEffectTitle>());
	m_fadeEffects.push_back(std::make_unique<ChangeEffectStageSelect>());
	m_fadeEffects.push_back(std::make_unique<ChangeEffectPlay>());
	m_fadeEffects.push_back(std::make_unique<ChangeEffectResult>());

	//	初期化を行う
	for (const auto& fadeEffect : m_fadeEffects)
	{
		fadeEffect->Initialize();
	}
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="timer">タイマー</param>
void ChageSceneEffect::Update(const DX::StepTimer& timer)
{
	for (const auto& fadeEffect : m_fadeEffects)
	{
		//	フラグがなければ帰れ
		if (fadeEffect->GetChangeFadeType() == ChangeEffect::ChangeSceneFadeType::None)	continue;

		//	経過時間を更新する
		fadeEffect->UpdateElapsedTime(timer);

		//	シーンのフェードの入場処理を行う
		if (fadeEffect->GetChangeFadeType() == ChangeEffect::ChangeSceneFadeType::To)
		{
			fadeEffect->ToChange();
		}
		//	シーンのフェードの退出処理を行う
		if (fadeEffect->GetChangeFadeType() == ChangeEffect::ChangeSceneFadeType::Out)
		{
			fadeEffect->OutChange();
		}
	}
}

/// <summary>
/// エフェクトの描画
/// </summary>
void ChageSceneEffect::DrawEffect()
{
	//	描画を開始する
	MyLib::ScreenResources::GetInstance()->GetSpriteBatch()->Begin();

	for (const auto& fadeEffect : m_fadeEffects)
	{
		if (fadeEffect->GetChangeFadeType() != ChangeEffect::ChangeSceneFadeType::None)
		{
			fadeEffect->Draw();
		}
	}
	//	描画を終了する
	MyLib::ScreenResources::GetInstance()->GetSpriteBatch()->End();
}

/// <summary>
/// シーン遷移のエフェクトの要求を設定
/// </summary>
/// <param name="requestType">リクエストタイプ</param>
/// <param name="fadeType">ファードタイプ</param>
void ChageSceneEffect::RequestChangeEffect(const ChangeEffect::ChangeSceneType& requestType, const ChangeEffect::ChangeSceneFadeType& fadeType)
{
	for (const auto& fadeEffect : m_fadeEffects)
	{
		//	対象のフェード対象を探す 
		if (fadeEffect->GetChangeType() == requestType)
		{
			//	フェードタイプをリセットする
			fadeEffect->SetSceneFadeType(fadeType);
			//	時間と色情報はリセットする
			fadeEffect->ResetColorAndTime();
			//	事前に初期化するものがあれば初期化を行う
			fadeEffect->PreInitialize();
		}
	}
}